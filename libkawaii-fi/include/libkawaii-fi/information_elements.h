#ifndef INFORMATION_ELEMENTS_H
#define INFORMATION_ELEMENTS_H

#include "ht_capabilities.h"
#include "ht_operations.h"
#include "vht_capabilities.h"
#include "vht_operations.h"

#include <QDBusArgument>
#include <QMetaType>
#include <QVector>

struct InformationElements {
	QString ssid;
	unsigned int channel = 0;
	QVector<double> basic_rates;
	QVector<double> supported_rates;
	HtCapabilities ht_capabilities;
	HtOperations ht_operations;
	VhtCapabilities vht_capabilities;
	VhtOperations vht_operations;
};
Q_DECLARE_METATYPE(InformationElements)

// Marshall the InformationElements data into a D-Bus argument
QDBusArgument &operator<<(QDBusArgument &argument, const InformationElements &ies);

// Retrieve the InformationElements data from the D-Bus argument
const QDBusArgument &operator>>(const QDBusArgument &argument, InformationElements &ies);

#endif // INFORMATION_ELEMENTS_H
