#include "access_point_table_model.h"

#include <QAbstractTableModel>
#include <QVariant>
#include <QVector>
#include <libkawaii-fi/access_point.h>

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

	if (role != Qt::DisplayRole) {
		return QVariant();
	}
	const AccessPoint &ap = _accessPoints[index.row()];

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
		return ap.information_elements.channel;
	case ApColumn::ChannelWidth:
		if (ap.information_elements.vht_operations.supported) {
			switch (ap.information_elements.vht_operations.channel_width) {
			case VhtChannelWidth::TwentyOrFortyMhz:
				return ap.information_elements.ht_operations.secondary_channel_offset ==
				                       SecondaryChannelOffset::NoSecondaryChannel
				               ? "20 MHz"
				               : "40 MHz";
			case VhtChannelWidth::EightyMhz:
				return "80 MHz";
			case VhtChannelWidth::OneSixtyMhz:
				return "160 MHz";
			case VhtChannelWidth::EightyPlusEightyMhz:
				return "80+80 MHz";
			}
		} else if (ap.information_elements.ht_operations.supported) {
			return ap.information_elements.ht_operations.secondary_channel_offset ==
			                       SecondaryChannelOffset::NoSecondaryChannel
			               ? "20 MHz"
			               : "40 MHz";
		}
		return "20 MHz";
	case ApColumn::SignalStrength:
		return QString::number(static_cast<double>(ap.signal_strength_mbm) / 100, 'g', 2) + " dBm";
	case ApColumn::Protocol:
		return protocols_string(ap.protocols);
	case ApColumn::BasicRates:
		return supported_rates_string(ap.information_elements.basic_rates);
	case ApColumn::SupportedRates:
		return supported_rates_string(ap.information_elements.supported_rates);
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
		case ApColumn::BasicRates:
			return tr("Basic Rates");
		case ApColumn::SupportedRates:
			return tr("Supported Rates");
		}
	}

	return QVariant();
}
