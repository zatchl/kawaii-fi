#ifndef ACCESS_POINT_SCANNER_H
#define ACCESS_POINT_SCANNER_H

#include "libkawaii-fi/access_point.h"
#include "libkawaii-fi/wifi_device.h"

#include <NetworkManagerQt/ConnectionSettings>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QtCore>

namespace KawaiiFi::Scanning {
	class AccessPointScanner : public QObject {
		Q_OBJECT
	public:
		explicit AccessPointScanner(QObject *parent = nullptr);

		void set_is_scanning(bool is_scanning);
		void set_wifi_device(const QString &device_name);
		void set_wifi_device(Device *wifi_device);

		[[nodiscard]] const QVector<AccessPoint> *access_points() const;
		[[nodiscard]] QStringList wifi_device_names() const;

	signals:
		void access_points_changed(const QString &interface_name);

	private:
		Device *selected_wifi_device_ = nullptr;
		QVector<Device *> wifi_devices_;
	};
} // namespace KawaiiFi::Scanning

#endif // ACCESS_POINT_SCANNER_H
