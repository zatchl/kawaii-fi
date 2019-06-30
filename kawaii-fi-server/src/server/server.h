#ifndef SERVER_H
#define SERVER_H

#include <QHash>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QtDBus/QDBusObjectPath>
#include <libkawaii-fi/access_point.h>

namespace KawaiiFi {
	class Server : public QObject {
		Q_OBJECT
		Q_CLASSINFO("D-Bus Interface", "org.kawaiifi.Server")
	public:
		explicit Server(QObject *parent = nullptr);
		~Server();

	signals:
		void wifi_scan_completed(const QString &nicName);

	public slots:
		QStringList wireless_nic_names();
		QVector<AccessPoint> access_points(const QString &nicName);
		void trigger_wifi_scan(const QString &nicName);
	};
} // namespace KawaiiFi

#endif // SERVER_H
