#ifndef WIFI_DEVICE_H
#define WIFI_DEVICE_H

#include "access_point.h"

#include <NetworkManagerQt/WirelessDevice>
#include <QByteArrayData>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QVector>

class WifiDevice : public QObject {
	Q_OBJECT
public:
	explicit WifiDevice(const NetworkManager::WirelessDevice::Ptr &dbus_device,
	                    QObject *parent = nullptr);

	void request_scan();
	void start_scanning(int interval_sec);
	void stop_scanning();

	[[nodiscard]] const QVector<AccessPoint> &access_points() const;

	[[nodiscard]] int bit_rate_kbps() const;
	[[nodiscard]] const QString &hardware_address() const;
	[[nodiscard]] const QString &permanent_hardware_address() const;
	[[nodiscard]] const QString &interface_name() const;
	[[nodiscard]] NetworkManager::WirelessDevice::OperationMode mode() const;
	[[nodiscard]] NetworkManager::WirelessDevice::Capabilities wireless_capabilities() const;
	[[nodiscard]] unsigned int interface_index() const;

signals:
	void access_points_changed(const QString &wifi_device_name);

private:
	const NetworkManager::WirelessDevice::Ptr dbus_device_;

	QVector<AccessPoint> access_points_;

	const int bit_rate_kbps_;
	const QString hardware_address_;
	const QString permanent_hardware_address_;
	const QString interface_name_;
	const NetworkManager::WirelessDevice::OperationMode mode_;
	const NetworkManager::WirelessDevice::Capabilities wireless_capabilities_;
	const unsigned int interface_index_;

	QTimer *const scan_timer_ = new QTimer(this);
};

#endif // WIFI_DEVICE_H
