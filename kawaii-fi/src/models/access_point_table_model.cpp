#include "access_point_table_model.h"

#include <QAbstractTableModel>
#include <QVariant>
#include <QVector>
#include <libkawaii-fi/access_point.h>

using namespace KawaiiFi;

AccessPointTableModel::AccessPointTableModel(QObject *parent) : QAbstractTableModel(parent) {}

void AccessPointTableModel::update_access_points(const QVector<AccessPoint> &access_points)
{
	_accessPoints = access_points;
	emit layoutChanged();
}

int AccessPointTableModel::rowCount(const QModelIndex &) const { return _accessPoints.size(); }

int AccessPointTableModel::columnCount(const QModelIndex &) const { return 7; }

QVariant AccessPointTableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}

	if (role == Qt::DisplayRole) {
		const AccessPoint &ap = _accessPoints[index.row()];

		switch (index.column()) {
		case 0:
			return ap.ssid;
		case 1:
			return ap.bssid;
		case 2:
			return ap.vendor;
		case 3:
			return ap.frequency;
		case 4:
			return ap.channel;
		case 5:
			return ap.channel_width;
		case 6:
			return QString::number(static_cast<double>(ap.signal_strength_mbm) / 100, 'g', 2);
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
		case 0:
			return tr("Network Name");
		case 1:
			return tr("BSSID");
		case 2:
			return tr("Vendor");
		case 3:
			return tr("Frequency");
		case 4:
			return tr("Channel");
		case 5:
			return tr("Channel Width");
		case 6:
			return tr("Signal (dBm)");
		}
	}

	return QVariant();
}
