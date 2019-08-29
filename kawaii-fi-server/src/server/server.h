#ifndef SERVER_H
#define SERVER_H

#include <QByteArrayData>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <libkawaii-fi/access_point.h>

namespace KawaiiFi {
	class Server : public QObject {
		Q_OBJECT
		Q_CLASSINFO("D-Bus Interface", "org.kawaiifi.Server")
	public:
		explicit Server(QObject *parent = nullptr);
		~Server();
		[[nodiscard]] bool object_registered() const;
		[[nodiscard]] bool service_name_registered() const;

	signals:
		void wifi_scan_completed(const QString &nicName);

	public slots:
		QStringList wireless_nic_names();
		QVector<AccessPoint> access_points(const QString &nic_name);
		void trigger_wifi_scan(const QString &nic_name);

	private:
		bool object_registered_ = false;
		bool service_name_registered_ = false;
	};
} // namespace KawaiiFi

#endif // SERVER_H
