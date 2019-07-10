#include "libkawaii-fi/access_point.h"

#include <QDBusArgument>
#include <QString>

QDBusArgument &operator<<(QDBusArgument &argument, const AccessPoint &ap)
{
	QVector<int> protocols;
	for (Protocol p : ap.protocols) {
		protocols.append(static_cast<int>(p));
	}
	argument.beginStructure();
	argument << ap.bssid << static_cast<int>(ap.status) << ap.signal_strength_mbm << ap.frequency
	         << ap.age_ms << protocols << ap.information_elements;
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, AccessPoint &ap)
{
	int status;
	QVector<int> protocols;
	argument.beginStructure();
	argument >> ap.bssid >> status >> ap.signal_strength_mbm >> ap.frequency >> ap.age_ms >>
	        protocols >> ap.information_elements;
	argument.endStructure();
	ap.status = static_cast<ConnectionStatus>(status);
	for (int i : protocols) {
		ap.protocols.append(static_cast<Protocol>(i));
	}
	return argument;
}

bool operator==(const AccessPoint &lhs, const AccessPoint &rhs) { return lhs.bssid == rhs.bssid; }

bool operator!=(const AccessPoint &lhs, const AccessPoint &rhs) { return !(lhs == rhs); }
