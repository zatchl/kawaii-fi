#include "libkawaii-fi/wifi_device.h"

#include "libkawaii-fi/access_point.h"
#include "netlink/nl_wifi_scan.h"

#include <QByteArray>
#include <net/if.h>

namespace KawaiiFi {
	Device::Device(const NetworkManager::WirelessDevice::Ptr &dbus_device, QObject *parent)
	    : QObject(parent), dbus_device_(dbus_device), bit_rate_kbps_(dbus_device->bitRate()),
	      hardware_address_(dbus_device->hardwareAddress()),
	      permanent_hardware_address_(dbus_device->permanentHardwareAddress()),
	      interface_name_(dbus_device->interfaceName()), mode_(dbus_device->mode()),
	      wireless_capabilities_(dbus_device->wirelessCapabilities()),
	      interface_index_(if_nametoindex(dbus_device->interfaceName().toLocal8Bit().constData()))
	{
		// Request a new scan for access points when the timer times out
		connect(scan_timer_, &QTimer::timeout, this, &Device::request_scan);

		// Update the collection of access points after a scan has completed
		connect(dbus_device_.get(), &NetworkManager::WirelessDevice::lastScanChanged, [this]() {
			if (update_aps_using_last_scan(access_points_, interface_index_) &&
			    scan_timer_->isActive()) {
				emit access_points_changed(dbus_device_->interfaceName());
			}
		});
	}

	void Device::request_scan()
	{
		if (dbus_device_ != nullptr) {
			dbus_device_->requestScan();
		}
	}

	void Device::start_scanning(int interval_sec)
	{
		request_scan();
		constexpr int msec_per_sec = 1000;
		scan_timer_->start(interval_sec * msec_per_sec);
	}

	void Device::stop_scanning() { scan_timer_->stop(); }

	const QVector<AccessPoint> &Device::access_points() const { return access_points_; }

	int Device::bit_rate_kbps() const { return bit_rate_kbps_; }

	const QString &Device::interface_name() const { return interface_name_; }

	const QString &Device::hardware_address() const { return hardware_address_; }

	const QString &Device::permanent_hardware_address() const
	{
		return permanent_hardware_address_;
	}

	NetworkManager::WirelessDevice::OperationMode Device::mode() const { return mode_; }

	NetworkManager::WirelessDevice::Capabilities Device::wireless_capabilities() const
	{
		return wireless_capabilities_;
	}

	unsigned int Device::interface_index() const { return interface_index_; }
} // namespace KawaiiFi
