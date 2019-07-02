#include "nl_wifi_parse.h"

#include <QLatin1Char>
#include <QString>
#include <libnl3/netlink/attr.h>
#include <libnl3/netlink/data.h>

QString KawaiiFi::parse_bssid(nlattr *bssid_attr)
{
	const uint8_t *bssid_bytes = static_cast<uint8_t *>(nla_data(bssid_attr));
	const int field_width = 2;
	const int base = 16;
	const QLatin1Char fill_char = QLatin1Char('0');
	return QString("%1:%2:%3:%4:%5:%6")
	        .arg(*bssid_bytes, field_width, base, fill_char)
	        .arg(*(bssid_bytes + 1), field_width, base, fill_char)
	        .arg(*(bssid_bytes + 2), field_width, base, fill_char)
	        .arg(*(bssid_bytes + 3), field_width, base, fill_char)
	        .arg(*(bssid_bytes + 4), field_width, base, fill_char)
	        .arg(*(bssid_bytes + 5), field_width, base, fill_char);
}

unsigned int KawaiiFi::parse_frequency(nlattr *frequency_attr)
{
	return nla_get_u32(frequency_attr);
}

unsigned int KawaiiFi::parse_channel_width(nlattr *channel_width_attr)
{
	return nla_get_u32(channel_width_attr);
}

KawaiiFi::InformationElements KawaiiFi::parse_information_elements(nlattr *ies_attr)
{
	InformationElements ie;

	const uint8_t *ies_bytes = static_cast<uint8_t *>(nla_data(ies_attr));
	int ie_len = nla_len(ies_attr);
	while (ie_len >= 2 && ie_len >= ies_bytes[1]) {
		uint8_t element_len = ies_bytes[1];
		switch (ies_bytes[0]) {
		case 0:
			if (element_len > 0 && element_len <= 32) {
				QString ssid;
				for (int i = 0; i < element_len; ++i) {
					if (ies_bytes[i + 2] != ' ' && ies_bytes[i + 2] != '\\') {
						ssid.append(ies_bytes[i + 2]);
					} else if (ies_bytes[i + 2] == ' ' && (i != 0 && i != element_len - 1)) {
						ssid.append(" ");
					}
				}
				ie.ssid = ssid;
			}
			break;
		}
		ie_len -= ies_bytes[1] + 2;
		ies_bytes += ies_bytes[1] + 2;
	}
	return ie;
}

unsigned int KawaiiFi::parse_tsf(nlattr *tsf_attr) { return 0; }

unsigned int KawaiiFi::parse_beacon_interval(nlattr *beacon_interval_attr) { return 0; }

unsigned int KawaiiFi::parse_age_ms(nlattr *age_attr) { return nla_get_u32(age_attr); }

int KawaiiFi::parse_signal_strength_mbm(nlattr *signal_strength_attr)
{
	return nla_get_s32(signal_strength_attr);
}
