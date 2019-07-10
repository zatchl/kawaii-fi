#ifndef NL_WIFI_PARSE_H
#define NL_WIFI_PARSE_H

#include <QString>
#include <QVector>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/information_elements.h>
#include <libnl3/netlink/attr.h>

namespace KawaiiFi {
	QString parse_bssid(nlattr *bssid_attr);
	ConnectionStatus parse_status(nlattr *status_attr);
	unsigned int parse_frequency(nlattr *frequency_attr);
	unsigned int parse_tsf(nlattr *tsf_attr);
	unsigned int parse_beacon_interval(nlattr *beacon_interval_attr);
	unsigned int parse_age_ms(nlattr *age_attr);
	int parse_signal_strength_mbm(nlattr *signal_strength_attr);
	InformationElements parse_information_elements(nlattr *ies_attr);
} // namespace KawaiiFi

#endif // NL_WIFI_PARSE_H
