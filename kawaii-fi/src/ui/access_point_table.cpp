#include "access_point_table.h"

#include "scanning/access_point_scanner.h"
#include "ui/filter-menus/access_point_filter_menu.h"
#include "ui/filter-menus/bssid_filter_menu.h"
#include "ui/filter-menus/channel_filter_menu.h"
#include "ui/filter-menus/channel_width_filter_menu.h"
#include "ui/filter-menus/protocol_filter_menu.h"
#include "ui/filter-menus/ssid_filter_menu.h"

#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QAbstractTableModel>
#include <QColor>
#include <QHeaderView>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QList>
#include <QModelIndex>
#include <QModelIndexList>
#include <QSet>
#include <QTableView>
#include <QVariant>
#include <QVector>
#include <algorithm>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/channel.h>
#include <libkawaii-fi/ies/ds_parameter.h>
#include <libkawaii-fi/ies/ht_operations.h>
#include <libkawaii-fi/ies/ssid.h>
#include <libkawaii-fi/ies/supported_rates.h>
#include <libkawaii-fi/ies/vht_operations.h>

class QWidget;

namespace {
	enum class ApColumn {
		SSID,
		BSSID,
		Frequency,
		Channel,
		ChannelWidth,
		SignalStrength,
		Protocol,
		Security,
		SupportedRates,
		Vendor
	};

	const int total_columns = static_cast<int>(ApColumn::Vendor) + 1;

	QString supported_rates_string(const QList<double> &supported_rates)
	{
		QString rates_string;
		for (int i = 0; i < supported_rates.size(); ++i) {
			if (i < supported_rates.size() - 1) {
				rates_string += QString::number(supported_rates[i]) + ", ";
			} else {
				rates_string += QString::number(supported_rates[i]);
			}
		}
		return rates_string + " Mbit/s";
	}

	QString protocols_string(const QVector<Protocol> &protocols)
	{
		QString protocol_string;
		for (Protocol p : protocols) {
			switch (p) {
			case Protocol::A:
				protocol_string.append("a/");
				break;
			case Protocol::B:
				protocol_string.append("b/");
				break;
			case Protocol::G:
				protocol_string.append("g/");
				break;
			case Protocol::N:
				protocol_string.append("n/");
				break;
			case Protocol::AC:
				protocol_string.append("ac/");
				break;
			case Protocol::AX:
				protocol_string.append("ax/");
				break;
			}
		}
		case ApColumn::SupportedRates:
			return ap.supported_rates().join(", ");
		case ApColumn::MaxRate:
			return ap.max_rate();
		}
		return protocol_string;
	}

	QString security_string(const QVector<Security> &security)
	{
		QString security_string;
		for (Security s : security) {
			switch (s) {
			case Security::None:
				security_string.append("None/");
				break;
			case Security::WEP:
				security_string.append("WEP/");
				break;
			case Security::WPA:
				security_string.append("WPA/");
				break;
			case Security::WPA2:
				security_string.append("WPA2/");
				break;
			case Security::WPA3:
				security_string.append("WPA3/");
				break;
			}
		}
		if (security_string.endsWith("/")) {
			security_string.chop(1);
		}
		return security_string;
	}
} // namespace

AccessPointSortFilterProxyModel::AccessPointSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool AccessPointSortFilterProxyModel::filterAcceptsRow(int source_row,
                                                       const QModelIndex &source_parent) const
{
	QModelIndex channel_index =
	        sourceModel()->index(source_row, static_cast<int>(ApColumn::Channel), source_parent);
	unsigned int channel = sourceModel()->data(channel_index, Qt::UserRole).toUInt();
	bool is_channel_acceptable = acceptable_channels_.contains(channel);

	QModelIndex channel_width_index = sourceModel()->index(
	        source_row, static_cast<int>(ApColumn::ChannelWidth), source_parent);
	unsigned int channel_width = sourceModel()->data(channel_width_index, Qt::UserRole).toUInt();
	bool is_channel_width_acceptable = acceptable_channel_widths_.contains(channel_width);

	QModelIndex protocols_index =
	        sourceModel()->index(source_row, static_cast<int>(ApColumn::Protocol), source_parent);
	QVector<Protocol> protocols =
	        sourceModel()->data(protocols_index, Qt::UserRole).value<QVector<Protocol>>();
	bool are_protocols_acceptable = false;
	for (auto protocol : protocols) {
		if (acceptable_protocols_.contains(protocol)) {
			are_protocols_acceptable = true;
			break;
		}
	}

	return is_channel_acceptable && is_channel_width_acceptable && are_protocols_acceptable;
}

void AccessPointSortFilterProxyModel::set_acceptable_channels(QSet<unsigned int> channels)
{
	acceptable_channels_ = channels;
	invalidateFilter();
}

void AccessPointSortFilterProxyModel::set_acceptable_channel_widths(
        QSet<unsigned int> channel_widths)
{
	acceptable_channel_widths_ = channel_widths;
	invalidateFilter();
}

void AccessPointSortFilterProxyModel::set_acceptable_protocols(QSet<Protocol> protocols)
{
	acceptable_protocols_ = protocols;
	invalidateFilter();
}

AccessPointTableModel::AccessPointTableModel(const AccessPointScanner &ap_scanner, QObject *parent)
    : QAbstractTableModel(parent), ap_scanner_(ap_scanner)
{
	connect(&ap_scanner_, &AccessPointScanner::access_points_updated, this,
	        &AccessPointTableModel::refresh_model);
}

int AccessPointTableModel::rowCount(const QModelIndex &) const
{
	return ap_scanner_.access_points().size();
}

int AccessPointTableModel::columnCount(const QModelIndex &) const { return total_columns; }

QVariant AccessPointTableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}

	const AccessPoint &ap = ap_scanner_.access_points()[index.row()];

	switch (role) {
	case Qt::DisplayRole:
		switch (static_cast<ApColumn>(index.column())) {
		case ApColumn::SSID:
			if (ap.information_elements().contains(WLAN_EID_SSID)) {
				Ssid ssid = ap.information_elements().value(WLAN_EID_SSID);
				return ssid.bytes();
			}
			return QVariant();
		case ApColumn::BSSID:
			return ap.bssid();
		case ApColumn::Vendor:
			return "";
		case ApColumn::Frequency:
			return QString("%1 MHz").arg(ap.frequency());
		case ApColumn::Channel:
			// For VHT channels, use the VHT convention of referencing the channel according to the
			// center frequency of the entire channel
			// For HT channels, use the HT convention of referencing the channel using the primary
			// channel and '+1' or '-1' if there's a secondary channel above or below the primary
			if (ap.information_elements().contains(WLAN_EID_VHT_OPERATION)) {
				const Channel channel = ap.channel();
				auto channel_string = QString::number(channel.number());
				if (channel.width() == ChannelWidth::EightyPlusEightyMhz) {
					channel_string.append(QString(", %1").arg(channel.number_two()));
				}
				return channel_string;
			} else if (ap.information_elements().contains(WLAN_EID_HT_OPERATION)) {
				switch (HtOperations(ap.information_elements().value(WLAN_EID_HT_OPERATION))
				                .secondary_channel_offset()) {
				case SecondaryChannelOffset::Above: // 40 MHz
					return QString("%1+1").arg(
					        DsParameter(ap.information_elements().value(WLAN_EID_DS_PARAMS))
					                .channel());
				case SecondaryChannelOffset::Below: // 40 MHz
					return QString("%1-1").arg(
					        DsParameter(ap.information_elements().value(WLAN_EID_DS_PARAMS))
					                .channel());
				case SecondaryChannelOffset::NoSecondaryChannel: // 20 MHz
					return DsParameter(ap.information_elements().value(WLAN_EID_DS_PARAMS))
					        .channel();
				}
			}
			return DsParameter(ap.information_elements().value(WLAN_EID_DS_PARAMS)).channel();
		case ApColumn::ChannelWidth:
			return channel_width_to_string(ap.channel_width());
		case ApColumn::SignalStrength:
			return QString("%1 dBm").arg(ap.signal_strength_dbm());
		case ApColumn::Protocol:
			return protocols_string(ap.protocols());
		case ApColumn::Security:
			return security_string(ap.security());
		case ApColumn::BasicRates: {
			auto supp_rates = SupportedRates(ap.information_elements().value(WLAN_EID_SUPP_RATES))
			                          .basic_rates();
			supp_rates.unite(
			        SupportedRates(ap.information_elements().value(WLAN_EID_EXT_SUPP_RATES))
			                .basic_rates());
			auto rate_list = supp_rates.toList();
			std::sort(rate_list.begin(), rate_list.end());
			return supported_rates_string(rate_list);
		}
		case ApColumn::SupportedRates: {
			auto supp_rates =
			        SupportedRates(ap.information_elements().value(WLAN_EID_SUPP_RATES)).rates();
			supp_rates.unite(
			        SupportedRates(ap.information_elements().value(WLAN_EID_EXT_SUPP_RATES))
			                .rates());
			auto rate_list = supp_rates.toList();
			std::sort(rate_list.begin(), rate_list.end());
			return supported_rates_string(rate_list);
		}
		}
		break;
	}

	return QVariant();
}

QVariant AccessPointTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	// The horizontal header contains the column names
	if (orientation == Qt::Orientation::Horizontal && role == Qt::DisplayRole) {
		switch (static_cast<ApColumn>(section)) {
		case ApColumn::SSID:
			return tr("SSID");
		case ApColumn::BSSID:
			return tr("BSSID");
		case ApColumn::Frequency:
			return tr("Frequency");
		case ApColumn::Channel:
			return tr("Channel");
		case ApColumn::ChannelWidth:
			return tr("Channel Width");
		case ApColumn::SignalStrength:
			return tr("Signal");
		case ApColumn::Protocol:
			return tr("Protocol");
		case ApColumn::Security:
			return tr("Security");
		case ApColumn::SupportedRates:
			return tr("Supported Rates");
		case ApColumn::Vendor:
			return tr("Vendor");
		}
	}

	// The vertical header contains the color associated with each access point
	if (orientation == Qt::Orientation::Vertical && role == Qt::BackgroundRole &&
	    section < ap_scanner_.access_points().size()) {
		return ap_scanner_.access_point_colors()[ap_scanner_.access_points()[section].bssid()];
	}

	return QVariant();
}

void AccessPointTableModel::refresh_model()
{
	emit layoutAboutToBeChanged();
	emit layoutChanged();
}

AccessPointTableView::AccessPointTableView(QWidget *parent) : QTableView(parent)
{
	horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(horizontalHeader(), &QHeaderView::customContextMenuRequested, this,
	        &AccessPointTableView::handle_header_context_menu_requested);

	setSelectionBehavior(QAbstractItemView::SelectRows);
	setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
}

void AccessPointTableView::set_ap_scanner(const AccessPointScanner &ap_scanner)
{
	ap_sort_filter_proxy_model_->setSourceModel(new AccessPointTableModel(ap_scanner, this));
	ap_sort_filter_proxy_model_->setSortRole(Qt::UserRole);
	setModel(ap_sort_filter_proxy_model_);

	sortByColumn(static_cast<int>(ApColumn::SignalStrength), Qt::DescendingOrder);

	connect(selectionModel(), &QItemSelectionModel::selectionChanged, this,
	        &AccessPointTableView::handle_item_selected);

	ap_sort_filter_proxy_model_->set_acceptable_channels(channel_filter_menu_->channels());
	connect(channel_filter_menu_, &AccessPointFilterMenu::filter_changed, [this]() {
		ap_sort_filter_proxy_model_->set_acceptable_channels(channel_filter_menu_->channels());
	});
	ap_sort_filter_proxy_model_->set_acceptable_channel_widths(
	        channel_width_filter_menu_->channel_widths());
	connect(channel_width_filter_menu_, &AccessPointFilterMenu::filter_changed, [this]() {
		ap_sort_filter_proxy_model_->set_acceptable_channel_widths(
		        channel_width_filter_menu_->channel_widths());
	});
	ap_sort_filter_proxy_model_->set_acceptable_protocols(protocol_filter_menu_->protocols());
	connect(protocol_filter_menu_, &AccessPointFilterMenu::filter_changed, [this]() {
		ap_sort_filter_proxy_model_->set_acceptable_protocols(protocol_filter_menu_->protocols());
	});
}

AccessPointSortFilterProxyModel *AccessPointTableView::ap_sort_filter_proxy_model()
{
	return ap_sort_filter_proxy_model_;
}

SsidFilterMenu *AccessPointTableView::ssid_filter_menu() const { return ssid_filter_menu_; }

BssidFilterMenu *AccessPointTableView::bssid_filter_menu() const { return bssid_filter_menu_; }

ChannelFilterMenu *AccessPointTableView::channel_filter_menu() const
{
	return channel_filter_menu_;
}

ChannelWidthFilterMenu *AccessPointTableView::channel_width_filter_menu() const
{
	return channel_width_filter_menu_;
}

ProtocolFilterMenu *AccessPointTableView::protocol_filter_menu() const
{
	return protocol_filter_menu_;
}

void AccessPointTableView::handle_item_selected(const QItemSelection &selected,
                                                const QItemSelection &)
{
	if (selected.indexes().size() == 0) {
		return;
	}

	QModelIndex model_index = ap_sort_filter_proxy_model_->index(selected.indexes()[0].row(),
	                                                             static_cast<int>(ApColumn::BSSID));
	QVariant bssid = ap_sort_filter_proxy_model_->data(model_index);
	emit access_point_selected(bssid.toString());
}

void AccessPointTableView::handle_header_context_menu_requested(const QPoint &point)
{
	ApColumn column = static_cast<ApColumn>(horizontalHeader()->logicalIndexAt(point));
	switch (column) {
	case ApColumn::SSID:
		ssid_filter_menu_->popup(horizontalHeader()->mapToGlobal(point));
		break;
	case ApColumn::BSSID:
		bssid_filter_menu_->popup(horizontalHeader()->mapToGlobal(point));
		break;
	case ApColumn::Channel:
		channel_filter_menu_->popup(horizontalHeader()->mapToGlobal(point));
		break;
	case ApColumn::ChannelWidth:
		channel_width_filter_menu_->popup(horizontalHeader()->mapToGlobal(point));
		break;
	case ApColumn::Protocol:
		protocol_filter_menu_->popup(horizontalHeader()->mapToGlobal(point));
		break;
	default:
		break;
	}
}
