#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include <QDBusArgument>
#include <QString>
#include <QVector>

struct AccessPoint {
	QString bssid;
	QString ssid;
	QString vendor;
	int signal_strength_mbm = 0;
	unsigned int frequency = 0;
	unsigned int channel = 0;
	unsigned int channel_width = 0;
	unsigned int age_ms = 0;
	QVector<double> basic_rates;
	QVector<double> supported_rates;
};
Q_DECLARE_METATYPE(AccessPoint)

// Marshall the AccessPoint data into a D-Bus argument
QDBusArgument &operator<<(QDBusArgument &argument, const AccessPoint &ap);

// Retrieve the AccessPoint data from the D-Bus argument
const QDBusArgument &operator>>(const QDBusArgument &argument, AccessPoint &ap);

bool operator==(const AccessPoint &lhs, const AccessPoint &rhs);

bool operator!=(const AccessPoint &lhs, const AccessPoint &rhs);

#endif // ACCESS_POINT_H
