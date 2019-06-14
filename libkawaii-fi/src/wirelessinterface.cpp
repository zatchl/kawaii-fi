#include <libkawaii-fi/wirelessinterface.h>

#include <net/if.h>

#include <QString>
#include <QVector>
#include <cstring>
#include <ifaddrs.h>
#include <libkawaii-fi/accesspoint.h>
#include <linux/wireless.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

using namespace KawaiiFi;

WirelessInterface::WirelessInterface(unsigned int index, const QString name)
    : _index(index), _name(name)
{
}

QString WirelessInterface::linkStatus() const
{
	return "";
}

int WirelessInterface::triggerScan() const
{
	return 0;
}

QVector<AccessPoint> WirelessInterface::scanResults() const
{
	QVector<AccessPoint> accessPoints;
	return accessPoints;
}

QVector<AccessPoint> WirelessInterface::waitForNewScanResults() const
{
	triggerScan();
	return scanResults();
}

bool WirelessInterface::supportsTwoPointFourGhz() const
{
	return _twoPointFourGhzChannels.size() > 0;
}

bool WirelessInterface::supportsFiveGhz() const
{
	return _fiveGhzChannels.size() > 0;
}

QString WirelessInterface::name() const
{
	return _name;
}

unsigned int WirelessInterface::index() const
{
	return _index;
}

QVector<unsigned int> WirelessInterface::twoPointFourGhzChannels() const
{
	return _twoPointFourGhzChannels;
}

QVector<unsigned int> WirelessInterface::fiveGhzChannels() const
{
	return _fiveGhzChannels;
}

// The following is adapted from https://gist.github.com/edufelipe/6108057
namespace {
	bool isInterfaceWireless(const char *ifname)
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
} // namespace

QVector<WirelessInterface> KawaiiFi::getWirelessInterfaces()
{
	QVector<WirelessInterface> wirelessInterfaces;

	//	// Get the addresses of all the interfaces
	struct ifaddrs *ifaddr;
	if (getifaddrs(&ifaddr) == -1) {
		return wirelessInterfaces;
	}

	//	// If any of the interfaces are wireless, add them to the vector
	for (struct ifaddrs *ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == nullptr || ifa->ifa_addr->sa_family != AF_PACKET) {
			continue;
		}

		if (isInterfaceWireless(ifa->ifa_name)) {
			wirelessInterfaces.append(
			        WirelessInterface(if_nametoindex(ifa->ifa_name), ifa->ifa_name));
		}
	}
	freeifaddrs(ifaddr);
	return wirelessInterfaces;
}
