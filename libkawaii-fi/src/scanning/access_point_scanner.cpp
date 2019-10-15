#include "libkawaii-fi/scanning/access_point_scanner.h"

#include "libkawaii-fi/wifi_device.h"

#include <NetworkManagerQt/Device>
#include <NetworkManagerQt/Manager>
#include <NetworkManagerQt/WirelessDevice>
#include <QString>
#include <QVector>
#include <algorithm>
#include <utility>

class AccessPoint;

namespace KawaiiFi::Scanning {
	AccessPointScanner::AccessPointScanner(QObject *parent) : QObject(parent)
	{
		const auto network_interfaces = NetworkManager::networkInterfaces();
		for (const NetworkManager::Device::Ptr &device : network_interfaces) {
			if (device->type() == NetworkManager::Device::Wifi) {
				auto *wifi_device =
				        new Device(device.objectCast<NetworkManager::WirelessDevice>(), this);
				connect(wifi_device, &Device::access_points_changed,
				        [this](const QString &interface_name) {
					        emit access_points_changed(interface_name);
				        });
				wifi_devices_.append(wifi_device);
			}
		}
	}

	void AccessPointScanner::set_is_scanning(bool is_scanning)
	{
		if ((selected_wifi_device_ != nullptr) && is_scanning) {
			selected_wifi_device_->start_scanning(10);
		} else if (selected_wifi_device_ != nullptr) {
			selected_wifi_device_->stop_scanning();
		}
	}

	void AccessPointScanner::set_wifi_device(const QString &device_name)
	{
		auto it = std::find_if(wifi_devices_.begin(), wifi_devices_.end(),
		                       [&device_name](const auto device) {
			                       return device->interface_name() == device_name;
		                       });

		if (it != wifi_devices_.end()) {
			set_wifi_device(*it);
		}
	}

	void AccessPointScanner::set_wifi_device(Device *wifi_device)
	{
		// Disconnect from the previous device's signals
		if (selected_wifi_device_ != nullptr) {
			selected_wifi_device_->stop_scanning();
		}

		selected_wifi_device_ = wifi_device;
		selected_wifi_device_->start_scanning(10);
	}

	const QVector<AccessPoint> *AccessPointScanner::access_points() const
	{
		return selected_wifi_device_ != nullptr ? &selected_wifi_device_->access_points() : nullptr;
	}

	QStringList AccessPointScanner::wifi_device_names() const
	{
		QStringList wireless_interfaces;
		const auto network_interfaces = NetworkManager::networkInterfaces();
		for (const NetworkManager::Device::Ptr &device : network_interfaces) {
			if (device->type() == NetworkManager::Device::Wifi) {
				wireless_interfaces.append(device->interfaceName());
			}
		}
		return wireless_interfaces;
	}
} // namespace KawaiiFi::Scanning
