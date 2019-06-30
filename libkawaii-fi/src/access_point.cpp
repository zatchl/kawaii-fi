#include "libkawaii-fi/access_point.h"

#include <QDBusArgument>
#include <QString>

QDBusArgument &operator<<(QDBusArgument &argument, const AccessPoint &ap)
{
	argument.beginStructure();
	argument << ap.bssid << ap.ssid << ap.vendor << ap.frequency << ap.channel << ap.channelWidth
	         << ap.signalStrength;
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, AccessPoint &ap)
{
	argument.beginStructure();
	argument >> ap.bssid >> ap.ssid >> ap.vendor >> ap.frequency >> ap.channel >> ap.channelWidth >>
	        ap.signalStrength;
	argument.endStructure();
	return argument;
}

bool operator==(const AccessPoint &lhs, const AccessPoint &rhs)
{
	return lhs.bssid == rhs.bssid;
}

bool operator!=(const AccessPoint &lhs, const AccessPoint &rhs)
{
	return !(lhs == rhs);
}