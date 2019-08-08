#ifndef ACCESS_POINT_TABLE_H
#define ACCESS_POINT_TABLE_H

#include <QAbstractTableModel>
#include <QSortFilterProxyModel>
#include <QString>
#include <QTableView>
#include <QVariant>
#include <QtCore>

class AccessPointScanner;
class QWidget;

class AccessPointTableModel : public QAbstractTableModel {
	Q_OBJECT
public:
	AccessPointTableModel(const AccessPointScanner &ap_scanner, QObject *parent = nullptr);
	[[nodiscard]] int rowCount(const QModelIndex &parent) const override;
	[[nodiscard]] int columnCount(const QModelIndex &parent) const override;
	[[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
	[[nodiscard]] QVariant headerData(int section, Qt::Orientation, int role) const override;

private:
	void refresh_model();
	const AccessPointScanner &ap_scanner_;
};

class AccessPointTableView : public QTableView {
	Q_OBJECT
public:
	AccessPointTableView(const AccessPointScanner &ap_scanner, QWidget *parent = nullptr);

signals:
	void access_point_selected(const QString &bssid);

private:
	void handle_item_selected(const QItemSelection &selected, const QItemSelection &deselected);
	QSortFilterProxyModel *const ap_proxy_model_ = new QSortFilterProxyModel(this);
};

#endif // ACCESS_POINT_TABLE_H
