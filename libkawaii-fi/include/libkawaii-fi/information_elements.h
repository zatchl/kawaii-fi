#ifndef INFORMATION_ELEMENTS_H
#define INFORMATION_ELEMENTS_H

#include <QDBusArgument>
#include <QMetaType>
#include <QVector>
#include <libkawaii-fi/ht_capabilities.h>
#include <libkawaii-fi/ht_operations.h>
#include <libkawaii-fi/vht_capabilities.h>
#include <libkawaii-fi/vht_operations.h>

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
