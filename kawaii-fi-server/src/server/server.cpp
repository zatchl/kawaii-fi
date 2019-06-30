#include "server.h"

#include "kawaiifi_server_adaptor.h"
#include "netlink/nl_wifi_scan.h"

// clang-format off
#include <net/if.h>
// clang-format on
#include <QDBusConnection>
#include <QDBusMetaType>
#include <QDBusObjectPath>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <cstring>
#include <ifaddrs.h>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/kawaiifi.h>
#include <linux/wireless.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

KawaiiFi::Server::Server(QObject *parent) : QObject(parent)
{
	qRegisterMetaType<AccessPoint>("AccessPoint");
	qDBusRegisterMetaType<AccessPoint>();
	qDBusRegisterMetaType<QVector<AccessPoint>>();

	new KawaiiFiServerAdaptor(this);
	QDBusConnection::systemBus().registerObject(
	        KawaiiFi::ServerObjectPath, this,
	        QDBusConnection::RegisterOption::ExportAllSlots |
	                QDBusConnection::RegisterOption::ExportAllSignal);
}

KawaiiFi::Server::~Server()
{
	QDBusConnection::systemBus().unregisterObject(KawaiiFi::ServerObjectPath);
}

namespace {
	// Adapted from https://gist.github.com/edufelipe/6108057
	bool is_nic_wireless(const char *ifname)
	{
		int sock = -1;
		struct iwreq pwrq;
		memset(&pwrq, 0, sizeof(pwrq));
		strncpy(pwrq.ifr_name, ifname, IFNAMSIZ);

		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			return false;
		}

		if (ioctl(sock, SIOCGIWNAME, &pwrq) != -1) {
			close(sock);
			return true;
		}

		close(sock);
		return false;
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

QStringList KawaiiFi::Server::wireless_nic_names()
{
	QStringList nic_names;
	for (const QString &nic_name : wireless_nics().keys()) {
		nic_names.append(nic_name);
	}
	return nic_names;
}

void KawaiiFi::Server::trigger_wifi_scan(const QString &nicName)
{
	// Check to see if the given interface name is connected
	QHash<QString, unsigned int> nics = wireless_nics();
	if (!nics.contains(nicName)) {
		return;
	}

	// Attempt to trigger a Wi-Fi scan using the interface's index
	// Return if triggering the scan was not successful
	if (trigger_scan_with_interface(nics[nicName])) {
		return;
	}

	// Wait for the new scan results to come in
	wait_for_new_wifi_scan_results();
	emit wifi_scan_completed(nicName);
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
