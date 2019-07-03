#include "access_point_table_model.h"

#include <QAbstractTableModel>
#include <QVariant>
#include <QVector>
#include <libkawaii-fi/access_point.h>

using namespace KawaiiFi;

namespace {
	enum Column {
		SSID,
		BSSID,
		Vendor,
		Frequency,
		Channel,
		ChannelWidth,
		SignalStrength,
		BasicRates,
		SupportedRates
	};
	const int total_columns = 9;

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
		return rates_string;
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

	if (role == Qt::DisplayRole) {
		const AccessPoint &ap = _accessPoints[index.row()];

		switch (index.column()) {
		case Column::SSID:
			return ap.ssid;
		case Column::BSSID:
			return ap.bssid;
		case Column::Vendor:
			return ap.vendor;
		case Column::Frequency:
			return ap.frequency;
		case Column::Channel:
			return ap.channel;
		case Column::ChannelWidth:
			return ap.channel_width;
		case Column::SignalStrength:
			return QString::number(static_cast<double>(ap.signal_strength_mbm) / 100, 'g', 2);
		case Column::BasicRates:
			return supported_rates_string(ap.basic_rates);
		case Column::SupportedRates:
			return supported_rates_string(ap.supported_rates);
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
		switch (section) {
		case Column::SSID:
			return tr("SSID");
		case Column::BSSID:
			return tr("BSSID");
		case Column::Vendor:
			return tr("Vendor");
		case Column::Frequency:
			return tr("Frequency");
		case Column::Channel:
			return tr("Channel");
		case Column::ChannelWidth:
			return tr("Channel Width");
		case Column::SignalStrength:
			return tr("Signal (dBm)");
		case Column::BasicRates:
			return tr("Basic Rates (Mbps)");
		case Column::SupportedRates:
			return tr("Supported Rates (Mbps)");
		}
	}

	return QVariant();
}
