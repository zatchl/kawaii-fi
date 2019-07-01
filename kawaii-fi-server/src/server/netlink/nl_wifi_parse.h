#ifndef NL_WIFI_PARSE_H
#define NL_WIFI_PARSE_H

#include <QString>
#include <libnl3/netlink/attr.h>

namespace KawaiiFi {
	struct InformationElements {
		QString ssid;
		QString vendor;
	};

	QString parse_bssid(nlattr *bssid_attr);
	unsigned int parse_frequency(nlattr *frequency_attr);
	unsigned int parse_channel_width(nlattr *channel_width);
	unsigned int parse_tsf(nlattr *tsf_attr);
	unsigned int parse_beacon_interval(nlattr *beacon_interval_attr);
	unsigned int parse_age_ms(nlattr *age_attr);
	int parse_signal_strength_mbm(nlattr *signal_strength_attr);
	InformationElements parse_information_elements(nlattr *ies_attr);
} // namespace KawaiiFi

#endif // NL_WIFI_PARSE_H
