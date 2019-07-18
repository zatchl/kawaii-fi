#include "server.h"

#include "kawaiifi_server_adaptor.h"
#include "netlink/nl_wifi_scan.h"

// clang-format off
#include <net/if.h>
// clang-format on
#include <QArgument>
#include <QtConcurrent/QtConcurrentRun>
#include <QtCore>
#include <QDBusConnection>
#include <QDBusMetaType>
#include <QMetaObject>
#include <QMetaType>
#include <cstring>
#include <ifaddrs.h>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/kawaiifi.h>
#include <linux/if.h>
#include <linux/wireless.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

KawaiiFi::Server::Server(QObject *parent)
    : QObject(parent), object_registered_(QDBusConnection::systemBus().registerObject(
                               KawaiiFi::ServerObjectPath, this,
                               QDBusConnection::RegisterOption::ExportAllSlots |
                                       QDBusConnection::RegisterOption::ExportAllSignal)),
      service_name_registered_(QDBusConnection::systemBus().registerService(KawaiiFi::ServiceName))
{
	qRegisterMetaType<AccessPoint>("AccessPoint");
	qDBusRegisterMetaType<AccessPoint>();
	qDBusRegisterMetaType<QVector<AccessPoint>>();

	new KawaiiFiServerAdaptor(this);
}

KawaiiFi::Server::~Server()
{
	QDBusConnection::systemBus().unregisterObject(KawaiiFi::ServerObjectPath);
}

bool KawaiiFi::Server::object_registered() const { return object_registered_; }

bool KawaiiFi::Server::service_name_registered() const { return service_name_registered_; }

namespace {
	// Adapted from https://gist.github.com/edufelipe/6108057
	bool is_nic_wireless(const char *ifname)
	{
		// Create a structure for exchanging data with ioctl
		struct iwreq pwrq = {};
		memset(&pwrq, 0, sizeof(pwrq));
		// Set the structure's interface name to the name passed into this function
		strncpy(pwrq.ifr_name, ifname, IFNAMSIZ);

		// Create an IP domain stream socket
		// A return value of -1 indicates an error
		int sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == -1) {
			return false;
		}

		// Check for the presence of wireless extensions
		// A return value of -1 indicates an error
		if (ioctl(sock, SIOCGIWNAME, &pwrq) == -1) {
			close(sock);
			return false;
		}

		close(sock);
		return true;
	}

	QHash<QString, unsigned int> wireless_nics()
	{
		QHash<QString, unsigned int> wireless_nics;
		// Get the addresses of all the interfaces
		struct ifaddrs *ifaddr;
		if (getifaddrs(&ifaddr) == -1) {
			return wireless_nics;
		}

		// If any of the interfaces are wireless, add them to the dictionary
		for (struct ifaddrs *ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
			if (ifa->ifa_addr == nullptr || ifa->ifa_addr->sa_family != AF_PACKET) {
				continue;
			}

			if (is_nic_wireless(ifa->ifa_name)) {
				wireless_nics[ifa->ifa_name] = if_nametoindex(ifa->ifa_name);
			}
		}

		freeifaddrs(ifaddr);

		return wireless_nics;
	}
} // namespace

QStringList KawaiiFi::Server::wireless_nic_names() { return wireless_nics().keys(); }

void KawaiiFi::Server::trigger_wifi_scan(const QString &nic_name)
{
	QtConcurrent::run([=]() {
		// Check to see if the given interface name is connected
		const QHash<QString, unsigned int> nics = wireless_nics();
		if (!nics.contains(nic_name)) {
			return;
		}

		// Attempt to trigger a Wi-Fi scan using the interface's index
		// Return if triggering the scan was not successful
		if (trigger_scan_with_interface(nics[nic_name])) {
			return;
		}

		// Wait for the new scan results to come in
		// Return if waiting for the scan results was not successful
		if (wait_for_new_wifi_scan_results()) {
			return;
		}

		QMetaObject::invokeMethod(this, "wifi_scan_completed", Qt::QueuedConnection,
		                          Q_ARG(QString, nic_name));
	});
}

QVector<AccessPoint> KawaiiFi::Server::access_points(const QString &nic_name)
{
	// Check to see if the given interface name is connected
	QHash<QString, unsigned int> nics = wireless_nics();
	if (!nics.contains(nic_name)) {
		return QVector<AccessPoint>();
	}

	QVector<AccessPoint> access_points;
	get_wifi_scan_results(nics[nic_name], access_points);
	return access_points;
}
