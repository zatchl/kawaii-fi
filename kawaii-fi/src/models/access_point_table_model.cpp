#include "access_point_table_model.h"

#include <QColor>
#include <QModelIndex>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/channel.h>
#include <libkawaii-fi/ht_operations.h>
#include <libkawaii-fi/information_elements.h>
#include <libkawaii-fi/vht_operations.h>

using namespace KawaiiFi;

namespace {
	enum class ApColumn {
		SSID,
		BSSID,
		Vendor,
		Frequency,
		Channel,
		ChannelWidth,
		SignalStrength,
		Protocol,
		Security,
		BasicRates,
		SupportedRates
	};
	const int total_columns = static_cast<int>(ApColumn::SupportedRates) + 1;

	QString supported_rates_string(const QVector<double> &supported_rates)
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
		if (protocol_string.endsWith("/")) {
			protocol_string.chop(1);
		}
		return protocol_string;
	}
} // namespace

AccessPointTableModel::AccessPointTableModel(QObject *parent) : QAbstractTableModel(parent) {}

void AccessPointTableModel::update_access_points(const QVector<AccessPoint> &access_points)
{
	emit layoutAboutToBeChanged();
	_accessPoints = access_points;
	emit layoutChanged();
}

int AccessPointTableModel::rowCount(const QModelIndex &) const { return _accessPoints.size(); }

int AccessPointTableModel::columnCount(const QModelIndex &) const { return total_columns; }

QVariant AccessPointTableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}

	const AccessPoint &ap = _accessPoints[index.row()];

	switch (role) {
	case Qt::DisplayRole:
		switch (static_cast<ApColumn>(index.column())) {
		case ApColumn::SSID:
			return ap.information_elements.ssid;
		case ApColumn::BSSID:
			return ap.bssid;
		case ApColumn::Vendor:
			return "";
		case ApColumn::Frequency:
			return QString("%1 MHz").arg(ap.frequency);
		case ApColumn::Channel:
			// For VHT channels, use the VHT convention of referencing the channel according to the
			// center frequency of the entire channel
			// For HT channels, use the HT convention of referencing the channel using the primary
			// channel and '+1' or '-1' if there's a secondary channel above or below the primary
			if (ap.information_elements.vht_operations.supported) {
				const Channel channel = ap.channel();
				auto channel_string = QString::number(channel.number());
				if (channel.width() == ChannelWidth::EightyPlusEightyMhz) {
					channel_string.append(QString(", %1").arg(channel.number_two()));
				}
				return channel_string;
			} else if (ap.information_elements.ht_operations.supported) {
				switch (ap.information_elements.ht_operations.secondary_channel_offset) {
				case SecondaryChannelOffset::Above: // 40 MHz
					return QString("%1+1").arg(ap.information_elements.channel);
				case SecondaryChannelOffset::Below: // 40 MHz
					return QString("%1-1").arg(ap.information_elements.channel);
				case SecondaryChannelOffset::NoSecondaryChannel: // 20 MHz
					return ap.information_elements.channel;
				}
			}
			return ap.information_elements.channel;
		case ApColumn::ChannelWidth:
			switch (ap.channel_width()) {
			case ChannelWidth::TwentyMhz:
				return "20 MHz";
			case ChannelWidth::TwentyTwoMhz:
				return "22 MHz";
			case ChannelWidth::FortyMhz:
				return "40 MHz";
			case ChannelWidth::EightyMhz:
				return "80 MHz";
			case ChannelWidth::OneSixtyMhz:
				return "160 MHz";
			case ChannelWidth::EightyPlusEightyMhz:
				return "80+80 MHz";
			case ChannelWidth::Other:
				return QVariant();
			}
			break;
		case ApColumn::SignalStrength:
			return QString("%1 dBm").arg(ap.signal_strength_dbm());
		case ApColumn::Protocol:
			return protocols_string(ap.protocols);
		case ApColumn::Security:
			return "";
		case ApColumn::BasicRates:
			return supported_rates_string(ap.information_elements.basic_rates);
		case ApColumn::SupportedRates:
			return supported_rates_string(ap.information_elements.supported_rates);
		}
		break;
	case Qt::DecorationRole:
		switch (static_cast<ApColumn>(index.column())) {
		case ApColumn::SSID:
			return QColor("#" + QString(ap.bssid).remove(':'));
		default:
			return QVariant();
		}
	}

	return QVariant();
}

QVariant AccessPointTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole) {
		return QVariant();
	}

	if (orientation == Qt::Orientation::Horizontal) {
		switch (static_cast<ApColumn>(section)) {
		case ApColumn::SSID:
			return tr("SSID");
		case ApColumn::BSSID:
			return tr("BSSID");
		case ApColumn::Vendor:
			return tr("Vendor");
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
		case ApColumn::BasicRates:
			return tr("Basic Rates");
		case ApColumn::SupportedRates:
			return tr("Supported Rates");
		}
	}

	return QVariant();
}
