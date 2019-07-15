#ifndef NL_WIFI_PARSE_H
#define NL_WIFI_PARSE_H

#include <QString>
#include <libkawaii-fi/access_point.h>

struct InformationElements;
struct nlattr;

namespace KawaiiFi {
	QString parse_bssid(nlattr *bssid_attr);
	ConnectionStatus parse_status(nlattr *status_attr);
	unsigned int parse_frequency(nlattr *frequency_attr);
	unsigned int parse_tsf(nlattr *tsf_attr);
	unsigned int parse_beacon_interval(nlattr *beacon_interval_attr);
	unsigned int parse_age_ms(nlattr *age_attr);
	int parse_signal_strength_mbm(nlattr *signal_strength_attr);
	void parse_information_elements(nlattr *ies_attr, InformationElements &ies);
} // namespace KawaiiFi

#endif // NL_WIFI_PARSE_H
