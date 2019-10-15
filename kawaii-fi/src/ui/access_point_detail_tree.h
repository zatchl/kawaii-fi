#ifndef ACCESS_POINT_DETAIL_TREE_H
#define ACCESS_POINT_DETAIL_TREE_H

#include <QByteArrayData>
#include <QStandardItemModel>
#include <QString>
#include <QTreeView>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/scanning/access_point_scanner.h>

class QObject;
class QWidget;

class AccessPointDetailTreeView : public QTreeView {
	Q_OBJECT
public:
	explicit AccessPointDetailTreeView(QWidget *parent = nullptr);

	void set_ap_scanner(const KawaiiFi::Scanning::AccessPointScanner *ap_scanner);

public slots:
	void show_ies(const QString &bssid);

private:
	void show_ies_for_ap(const KawaiiFi::AccessPoint &ap);

	QStandardItemModel *const model_ = new QStandardItemModel(this);
	const KawaiiFi::Scanning::AccessPointScanner *ap_scanner_ = nullptr;
};

#endif // ACCESS_POINT_DETAIL_TREE_H
