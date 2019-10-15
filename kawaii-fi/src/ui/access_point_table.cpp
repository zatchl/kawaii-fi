#include "access_point_table.h"

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
#include <QFont>
#include <QHeaderView>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QModelIndexList>
#include <QRegExp>
#include <QSet>
#include <QStringList>
#include <QTableView>
#include <QVariant>
#include <QVector>
#include <QWidget>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/channel.h>
#include <libkawaii-fi/scanning/access_point_scanner.h>
#include <libkawaii-fi/security.h>
#include <libkawaii-fi/standard.h>

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
		MaxRate,
		Vendor
	};

	const int total_columns = static_cast<int>(ApColumn::Vendor) + 1;

	QVariant ap_attribute(const KawaiiFi::AccessPoint &ap, ApColumn attribute_column)
	{
		switch (attribute_column) {
		case ApColumn::SSID: {
			const QString &ssid = ap.ssid();
			return !ssid.isEmpty() ? ssid : "Hidden";
		}
		case ApColumn::BSSID:
			return ap.bssid();
		case ApColumn::Vendor:
			return "";
		case ApColumn::Frequency:
			return ap.frequency();
		case ApColumn::Channel:
			return ap.channel().number();
		case ApColumn::ChannelWidth:
			switch (ap.channel().width()) {
			case KawaiiFi::Channel::Width::TwentyMhz:
				return 20;
			case KawaiiFi::Channel::Width::TwentyTwoMhz:
				return 22;
			case KawaiiFi::Channel::Width::FortyMhz:
				return 40;
			case KawaiiFi::Channel::Width::EightyMhz:
				return 80;
			case KawaiiFi::Channel::Width::EightyPlusEightyMhz:
			case KawaiiFi::Channel::Width::OneSixtyMhz:
				return 160;
			case KawaiiFi::Channel::Width::Other:
				return ap.channel().width_mhz();
			}
		case ApColumn::SignalStrength:
			return ap.signal_dbm();
		case ApColumn::Protocol:
			return static_cast<int>(ap.standards());
		case ApColumn::Security: {
			QStringList security_list;
			for (KawaiiFi::Security::Protocol security : ap.security()) {
				security_list.append(KawaiiFi::Security::security_protocol_to_string(security));
			}
			const auto auth = ap.authentication();
			switch (auth) {
			case KawaiiFi::Security::AkmSuiteType::PSK:
				return security_list.join("/").append(" (PSK)");
			case KawaiiFi::Security::AkmSuiteType::IEEE_8021X:
				return security_list.join("/").append(" (802.1X)");
			case KawaiiFi::Security::AkmSuiteType::None:
				return security_list.join("/");
			}
		}
		case ApColumn::SupportedRates:
			return ap.supported_rates().join(", ");
		case ApColumn::MaxRate:
			return ap.max_rate();
		}
		return QVariant();
	}

	QVariant ap_attribute_for_display(const KawaiiFi::AccessPoint &ap, ApColumn attribute_column)
	{
		switch (attribute_column) {
		case ApColumn::Frequency:
			return QString("%0 MHz").arg(ap_attribute(ap, attribute_column).toUInt());
		case ApColumn::Channel:
			if (ap.channel().width() == KawaiiFi::Channel::Width::EightyPlusEightyMhz) {
				const KawaiiFi::Channel channel = ap.channel();
				return QString("%0, %1").arg(channel.number()).arg(channel.number_two());
			}
			return ap_attribute(ap, attribute_column);
		case ApColumn::ChannelWidth:
			if (ap.channel().width() == KawaiiFi::Channel::Width::EightyPlusEightyMhz) {
				return "80+80 MHz";
			}
			return QString("%0 MHz").arg(ap_attribute(ap, attribute_column).toUInt());
		case ApColumn::SignalStrength:
			return QString("%0 dBm").arg(ap_attribute(ap, attribute_column).toDouble());
		case ApColumn::Protocol: {
			return KawaiiFi::standards_to_string(ap.standards(), "/");
		}
		case ApColumn::SupportedRates:
			return QString("%0 Mbps").arg(ap_attribute(ap, attribute_column).toString());
		case ApColumn::MaxRate:
			return QString("%0 Mbps").arg(
			        QString::number(ap_attribute(ap, attribute_column).toDouble(), 'f', 1)
			                .remove(QRegExp("\\.?0+$"))); // Remove trailing zeros and decimal point
		default:
			return ap_attribute(ap, attribute_column);
		}
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
	auto protocols =
	        sourceModel()->data(protocols_index, Qt::UserRole).value<QVector<KawaiiFi::Standard>>();
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

void AccessPointSortFilterProxyModel::set_acceptable_protocols(KawaiiFi::Standards protocols)
{
	acceptable_protocols_ = protocols;
	invalidateFilter();
}

AccessPointTableModel::AccessPointTableModel(
        const KawaiiFi::Scanning::AccessPointScanner &ap_scanner, QObject *parent)
    : QAbstractTableModel(parent), ap_scanner_(ap_scanner)
{
	connect(&ap_scanner_, &KawaiiFi::Scanning::AccessPointScanner::access_points_changed, this,
	        &AccessPointTableModel::refresh_model);
}

int AccessPointTableModel::rowCount(const QModelIndex &) const
{
	return ap_scanner_.access_points() != nullptr ? ap_scanner_.access_points()->size() : 0;
}

int AccessPointTableModel::columnCount(const QModelIndex &) const { return total_columns; }

QVariant AccessPointTableModel::data(const QModelIndex &index, int role) const
{
	Q_ASSERT(checkIndex(index, QAbstractItemModel::CheckIndexOption::IndexIsValid |
	                                   QAbstractItemModel::CheckIndexOption::ParentIsInvalid));

	if (ap_scanner_.access_points() == nullptr) {
		return QVariant();
	}

	const KawaiiFi::AccessPoint &ap = ap_scanner_.access_points()->at(index.row());

	switch (role) {
	case Qt::DisplayRole:
		return ap_attribute_for_display(ap, static_cast<ApColumn>(index.column()));
	case Qt::UserRole:
		return ap_attribute(ap, static_cast<ApColumn>(index.column()));
	case Qt::FontRole:
		if (index.column() == static_cast<int>(ApColumn::SSID)) {
			QFont font;
			if (ap.ssid().isEmpty()) {
				font.setItalic(true);
			}
			return font;
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
		case ApColumn::MaxRate:
			return tr("Max Rate");
		case ApColumn::Vendor:
			return tr("Vendor");
		}
	}

	// The vertical header contains the color associated with each access point
	if (orientation == Qt::Orientation::Vertical && role == Qt::BackgroundRole &&
	    (ap_scanner_.access_points() != nullptr) && section < ap_scanner_.access_points()->size()) {
		return ap_scanner_.access_points()->at(section).color();
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

void AccessPointTableView::set_ap_scanner(const KawaiiFi::Scanning::AccessPointScanner &ap_scanner)
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
	ap_sort_filter_proxy_model_->set_acceptable_protocols(protocol_filter_menu_->standards());
	connect(protocol_filter_menu_, &AccessPointFilterMenu::filter_changed, [this]() {
		ap_sort_filter_proxy_model_->set_acceptable_protocols(protocol_filter_menu_->standards());
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
