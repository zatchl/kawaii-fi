#include "nl_wifi_parse.h"

#include "ieee80211.h"

#include <QByteArray>
#include <QVector>
#include <algorithm>
#include <cstdint>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/ht_capabilities.h>
#include <libkawaii-fi/ht_operations.h>
#include <libkawaii-fi/information_elements.h>
#include <libkawaii-fi/vht_capabilities.h>
#include <libkawaii-fi/vht_operations.h>
#include <libnl3/netlink/attr.h>
#include <linux/nl80211.h>
#include <string_view>

struct nlattr;

namespace {
	const unsigned int max_ssid_data_length = 32;
	const unsigned int ds_params_data_length = 1;

	const std::uint8_t supported_rate_mask = 0x7f; // 0111 1111
	const std::uint8_t basic_rate_mask = 0x80;     // 1000 0000
} // namespace

QString KawaiiFi::parse_bssid(nlattr *bssid_attr)
{
	return QByteArray::fromRawData(nla_get_string(bssid_attr), nla_len(bssid_attr)).toHex(':');
}

unsigned int KawaiiFi::parse_frequency(nlattr *frequency_attr)
{
	return nla_get_u32(frequency_attr);
}

void KawaiiFi::parse_information_elements(nlattr *ies_attr, InformationElements &ies)
{
	const auto ies_bytes = std::string_view(nla_get_string(ies_attr),
	                                        static_cast<unsigned int>(nla_len(ies_attr)));

	// The index of each element in ies_bytes
	std::string_view::size_type element_start = 0;
	// The length of the data portion of each element
	std::string_view::size_type element_data_length = static_cast<unsigned char>(ies_bytes[1]);
	// The total length of each element
	std::string_view::size_type element_length = element_data_length + 2;

	while (element_start + element_length < ies_bytes.size()) {
		// Element ID + Element Data Length + Element Data
		const std::string_view ie_bytes = ies_bytes.substr(element_start, element_length);
		// Only Element Data
		const std::string_view ie_data_bytes = ie_bytes.substr(2, element_data_length);
		// The ID of each element is the first byte
		const auto ie_id = static_cast<unsigned char>(ie_bytes[0]);
		switch (ie_id) {
		case WLAN_EID_SSID:
			if (element_data_length > max_ssid_data_length) {
				break;
			}
			ies.ssid = QString::fromLocal8Bit(ie_data_bytes.cbegin(),
			                                  static_cast<int>(ie_data_bytes.size()));
			break;
		case WLAN_EID_SUPP_RATES:
		case WLAN_EID_EXT_SUPP_RATES:
			for (const auto rate_byte : ie_data_bytes) {
				// The seven low-order bits are the rate as a multiple of 500 kbps
				// So divide by 2 to get the rate in mbps
				double rate_mbps = static_cast<double>(rate_byte & supported_rate_mask) / 2;
				ies.supported_rates.append(rate_mbps);
				// The most significant bit of the rate byte indicates whether the rate is
				// basic/mandatory
				if (rate_byte & basic_rate_mask) {
					ies.basic_rates.append(rate_mbps);
				}
			}
			std::sort(ies.basic_rates.begin(), ies.basic_rates.end());
			std::sort(ies.supported_rates.begin(), ies.supported_rates.end());
			break;
		case WLAN_EID_DS_PARAMS:
			if (element_data_length != ds_params_data_length) {
				break;
			}
			ies.channel = static_cast<unsigned char>(ie_data_bytes[0]);
			break;
		case WLAN_EID_HT_CAPABILITY:
			ies.ht_capabilities.parse_ie(ie_data_bytes);
			break;
		case WLAN_EID_HT_OPERATION:
			ies.ht_operations.parse_ie(ie_data_bytes);
			break;
		case WLAN_EID_VHT_CAPABILITY:
			ies.vht_capabilities.parse_ie(ie_data_bytes);
			break;
		case WLAN_EID_VHT_OPERATION:
			ies.vht_operations.parse_ie(ie_data_bytes);
			break;
		}

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
