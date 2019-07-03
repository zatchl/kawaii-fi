#include "libkawaii-fi/access_point.h"

#include <QDBusArgument>
#include <QString>

QDBusArgument &operator<<(QDBusArgument &argument, const AccessPoint &ap)
{
	argument.beginStructure();
	argument << ap.bssid << ap.ssid << ap.vendor << ap.frequency << ap.channel << ap.channel_width
	         << ap.signal_strength_mbm << ap.age_ms << ap.basic_rates << ap.supported_rates;
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, AccessPoint &ap)
{
	argument.beginStructure();
	argument >> ap.bssid >> ap.ssid >> ap.vendor >> ap.frequency >> ap.channel >>
	        ap.channel_width >> ap.signal_strength_mbm >> ap.age_ms >> ap.basic_rates >>
	        ap.supported_rates;
	argument.endStructure();
	return argument;
}

bool operator==(const AccessPoint &lhs, const AccessPoint &rhs) { return lhs.bssid == rhs.bssid; }

bool operator!=(const AccessPoint &lhs, const AccessPoint &rhs) { return !(lhs == rhs); }
