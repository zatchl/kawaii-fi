#ifndef ACCESSPOINTTABLEMODEL_H
#define ACCESSPOINTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QVector>
#include <libkawaii-fi/accesspoint.h>

namespace KawaiiFi {
	class AccessPointTableModel : public QAbstractTableModel {
		Q_OBJECT
	public:
		AccessPointTableModel(QObject *parent = nullptr);
		void updateAccessPoints(QVector<AccessPoint> accessPoints);
		int rowCount(const QModelIndex &parent) const override;
		int columnCount(const QModelIndex &parent) const override;
		QVariant data(const QModelIndex &index, int role) const override;
		QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	private:
		QVector<AccessPoint> _accessPoints;
	};
} // namespace KawaiiFi

#endif // ACCESSPOINTTABLEMODEL_H
