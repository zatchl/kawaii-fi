#ifndef ACCESS_POINT_SCANNER_H
#define ACCESS_POINT_SCANNER_H

#include "kawaiifi_server_interface.h"

#include <QDBusConnection>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QtCore>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/kawaiifi.h>

class QColor;

class AccessPointScanner : public QObject {
	Q_OBJECT
public:
	explicit AccessPointScanner(QObject *parent = nullptr);
	void scan(const QString &interface_name = "");
	[[nodiscard]] const QVector<AccessPoint> &access_points() const;
	[[nodiscard]] QHash<QString, QColor> access_point_colors() const;
	[[nodiscard]] QStringList wireless_nic_names() const;

signals:
	void access_points_updated(const QString &interface_name);

private:
	QVector<AccessPoint> access_points_;
	QHash<QString, QColor> access_point_colors_;
	QString interface_name_;
	org::kawaiifi::Server *const server_ = new org::kawaiifi::Server(
	        KawaiiFi::ServiceName, KawaiiFi::ServerObjectPath, QDBusConnection::systemBus(), this);
};

#endif // ACCESS_POINT_SCANNER_H
