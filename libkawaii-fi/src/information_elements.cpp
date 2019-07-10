#include "libkawaii-fi/information_elements.h"

#include <QDBusArgument>
#include <libkawaii-fi/ht_capabilities.h>

QDBusArgument &operator<<(QDBusArgument &argument, const InformationElements &ies)
{
	argument.beginStructure();
	argument << ies.ssid << ies.channel << ies.basic_rates << ies.supported_rates
	         << ies.ht_capabilities << ies.ht_operations << ies.vht_capabilities
	         << ies.vht_operations;
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, InformationElements &ies)
{
	argument.beginStructure();
	argument >> ies.ssid >> ies.channel >> ies.basic_rates >> ies.supported_rates >>
	        ies.ht_capabilities >> ies.ht_operations >> ies.vht_capabilities >> ies.vht_operations;
	argument.endStructure();
	return argument;
}
