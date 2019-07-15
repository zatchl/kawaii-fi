#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include "information_elements.h"

#include <QDBusArgument>
#include <QString>
#include <QVector>

enum class ConnectionStatus { Authenticated, Associated, Joined, Unknown };

enum class Protocol { B, A, G, N, AC, AX };

struct AccessPoint {
	QString bssid;
	ConnectionStatus status = ConnectionStatus::Unknown;
	int signal_strength_mbm = 0;
	unsigned int frequency = 0;
	unsigned int age_ms = 0;
	QVector<Protocol> protocols;
	InformationElements information_elements;
};
Q_DECLARE_METATYPE(AccessPoint)

// Marshall the AccessPoint data into a D-Bus argument
QDBusArgument &operator<<(QDBusArgument &argument, const AccessPoint &ap);

// Retrieve the AccessPoint data from the D-Bus argument
const QDBusArgument &operator>>(const QDBusArgument &argument, AccessPoint &ap);

bool operator==(const AccessPoint &lhs, const AccessPoint &rhs);

bool operator!=(const AccessPoint &lhs, const AccessPoint &rhs);

#endif // ACCESS_POINT_H
