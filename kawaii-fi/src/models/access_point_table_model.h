#ifndef ACCESSPOINTTABLEMODEL_H
#define ACCESSPOINTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QVariant>
#include <QVector>
#include <QtCore>
#include <libkawaii-fi/access_point.h>

class QColor;

namespace KawaiiFi {
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

	class AccessPointTableModel : public QAbstractTableModel {
		Q_OBJECT
	public:
		AccessPointTableModel(QObject *parent = nullptr);
		void update_access_points(const QVector<AccessPoint> &access_points);
		int rowCount(const QModelIndex &parent) const override;
		int columnCount(const QModelIndex &parent) const override;
		QVariant data(const QModelIndex &index, int role) const override;
		QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	private:
		QVector<AccessPoint> access_points_;
		QHash<QString, QColor> access_point_colors_;
	};
} // namespace KawaiiFi

#endif // ACCESSPOINTTABLEMODEL_H
