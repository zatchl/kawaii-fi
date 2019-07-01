#include "accesspointtablemodel.h"

#include <QAbstractTableModel>
#include <QVariant>
#include <QVector>
#include <libkawaii-fi/accesspoint.h>

using namespace KawaiiFi;

AccessPointTableModel::AccessPointTableModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void AccessPointTableModel::updateAccessPoints(QVector<KawaiiFi::AccessPoint> accessPoints)
{
	_accessPoints = accessPoints;
}

int AccessPointTableModel::rowCount(const QModelIndex &parent) const
{
	return _accessPoints.size();
}

int AccessPointTableModel::columnCount(const QModelIndex &parent) const
{
	return 6;
}

QVariant AccessPointTableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}

	if (role == Qt::DisplayRole) {
		const AccessPoint &ap = _accessPoints[index.row()];

		switch (index.column()) {
		case 0:
			return ap.ssid();
		case 1:
			return ap.bssid();
		case 2:
			return ap.vendor();
		case 3:
			return ap.channel();
		case 4:
			return ap.channelWidth();
		case 5:
			return ap.signalStrength();
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
			return tr("Channel");
		case 4:
			return tr("Channel Width");
		case 5:
			return tr("Signal Strength");
		}
	}

	return QVariant();
}
