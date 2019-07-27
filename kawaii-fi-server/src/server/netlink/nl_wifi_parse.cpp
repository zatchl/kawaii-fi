#include "nl_wifi_parse.h"

#include <QByteArray>
#include <QHashNode>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/information_element.h>
#include <libnl3/netlink/attr.h>
#include <linux/nl80211.h>
#include <string_view>

struct nlattr;

QString KawaiiFi::parse_bssid(nlattr *bssid_attr)
{
	return QByteArray::fromRawData(nla_get_string(bssid_attr), nla_len(bssid_attr)).toHex(':');
}

unsigned int KawaiiFi::parse_frequency(nlattr *frequency_attr)
{
	return nla_get_u32(frequency_attr);
}

unsigned int KawaiiFi::parse_tsf(nlattr *tsf_attr) { return 0; }

unsigned int KawaiiFi::parse_beacon_interval(nlattr *beacon_interval_attr) { return 0; }

unsigned int KawaiiFi::parse_age_ms(nlattr *age_attr) { return nla_get_u32(age_attr); }

int KawaiiFi::parse_signal_strength_mbm(nlattr *signal_strength_attr)
{
	return nla_get_s32(signal_strength_attr);
}

ConnectionStatus KawaiiFi::parse_status(nlattr *status_attr)
{
	switch (nla_get_u32(status_attr)) {
	case NL80211_BSS_STATUS_AUTHENTICATED:
		return ConnectionStatus::Authenticated;
	case NL80211_BSS_STATUS_ASSOCIATED:
		return ConnectionStatus::Associated;
	case NL80211_BSS_STATUS_IBSS_JOINED:
		return ConnectionStatus::Joined;
	default:
		return ConnectionStatus::Unknown;
	}
}

void KawaiiFi::parse_information_elements(nlattr *ies_attr,
                                          QHash<unsigned int, InformationElement> &ies)
{
	const auto ies_bytes = std::string_view(nla_get_string(ies_attr),
	                                        static_cast<unsigned int>(nla_len(ies_attr)));

	// The index of each element in ies_bytes
	std::string_view::size_type element_start = 0;
	// The length of the data portion of each element
	std::string_view::size_type element_data_length = static_cast<unsigned char>(ies_bytes[1]);
	// The total length of each element
	std::string_view::size_type element_length = element_data_length + 2;

	while (element_start + element_length <= ies_bytes.size()) {
		// Element ID + Element Data Length + Element Data
		const std::string_view ie_bytes = ies_bytes.substr(element_start, element_length);
		// Only Element Data
		const std::string_view ie_data_bytes = ie_bytes.substr(2, element_data_length);
		// The ID of each element is the first byte
		const auto ie_id = static_cast<unsigned char>(ie_bytes[0]);
		ies.insert(ie_id, InformationElement(ie_data_bytes.begin(),
		                                     static_cast<int>(element_data_length)));

		// The next element starts right after the current element
		element_start += element_length;
		if ((element_start + 1) >= ies_bytes.size()) {
			break;
		}
		// The second byte in each element is the length of the data
		element_data_length = static_cast<unsigned char>(ies_bytes[element_start + 1]);
		// The length of the next element is equal to the data length + 2
		// The 2 comes from the element ID byte and the element data length byte
		element_length = element_data_length + 2;
	}
}
