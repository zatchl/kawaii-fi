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
	const unsigned int ht_capability_data_length = 26;
	const unsigned int ht_operation_data_length = 22;
	const unsigned int vht_capability_data_length = 12;
	const unsigned int vht_operation_data_length = 5;

	const std::uint8_t supported_rate_mask = 0x7f;                   // 0111 1111
	const std::uint8_t basic_rate_mask = 0x80;                       // 1000 0000
	const std::uint8_t secondary_channel_offset_mask = 0x3;          // 0000 0011
	const std::uint8_t supported_channel_width_mask = 0x4;           // 0000 0100
	const std::uint8_t rifs_mask = 0x8;                              // 0000 1000
	const std::uint8_t ht_protection_mask = 0x3;                     // 0000 0011
	const std::uint8_t non_greenfield_stas_present_mask = 0x4;       // 0000 0100
	const std::uint8_t obss_non_ht_stas_present_mask = 0x10;         // 0001 0000
	const std::uint8_t dual_beacon_mask = 0x40;                      // 0100 0000
	const std::uint8_t dual_cts_protection_mask = 0x80;              // 1000 0000
	const std::uint8_t stbc_beacon_mask = 0x1;                       // 0000 0001
	const std::uint8_t lsig_txop_protection_full_support_mask = 0x2; // 0000 0010
	const std::uint8_t pco_active_mask = 0x4;                        // 0000 0100
	const std::uint8_t pco_phase_mask = 0x8;                         // 0000 1000
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
			if (element_data_length != ht_capability_data_length) {
				break;
			}
			ies.ht_capabilities.supported = true;
			break;
		case WLAN_EID_HT_OPERATION:
			if (element_data_length != ht_operation_data_length) {
				break;
			}
			ies.ht_operations.supported = true;
			ies.ht_operations.primary_channel = static_cast<unsigned char>(ie_data_bytes[0]);
			switch (ie_data_bytes[1] & secondary_channel_offset_mask) {
			case 0:
				ies.ht_operations.secondary_channel_offset =
				        SecondaryChannelOffset::NoSecondaryChannel;
				break;
			case 1:
				ies.ht_operations.secondary_channel_offset = SecondaryChannelOffset::Above;
				break;
			case 3:
				ies.ht_operations.secondary_channel_offset = SecondaryChannelOffset::Below;
				break;
			}
			ies.ht_operations.supported_channel_width =
			        (ie_data_bytes[1] & supported_channel_width_mask)
			                ? HtSupportedChannelWidth::TwentyOrFortyMhz
			                : HtSupportedChannelWidth::TwentyMhz;
			ies.ht_operations.rifs = ie_data_bytes[1] & rifs_mask;
			switch (ie_data_bytes[2] & ht_protection_mask) {
			case 0:
				ies.ht_operations.ht_protection = HtProtection::None;
				break;
			case 1:
				ies.ht_operations.ht_protection = HtProtection::Nonmember;
				break;
			case 2:
				ies.ht_operations.ht_protection = HtProtection::TwentyMhz;
				break;
			case 3:
				ies.ht_operations.ht_protection = HtProtection::NonHtMixed;
				break;
			}
			ies.ht_operations.non_greenfield_stas_present =
			        ie_data_bytes[2] & non_greenfield_stas_present_mask;
			ies.ht_operations.obss_non_ht_stas_present =
			        ie_data_bytes[2] & obss_non_ht_stas_present_mask;
			// ies.ht_operations.center_freq_segment_two = ;
			ies.ht_operations.dual_beacon = ie_data_bytes[4] & dual_beacon_mask;
			ies.ht_operations.dual_cts_protection = ie_data_bytes[4] & dual_cts_protection_mask;
			ies.ht_operations.stbc_beacon = ie_data_bytes[5] & stbc_beacon_mask;
			ies.ht_operations.lsig_txop_protection_full_support =
			        ie_data_bytes[5] & lsig_txop_protection_full_support_mask;
			ies.ht_operations.pco_active = ie_data_bytes[5] & pco_active_mask;
			ies.ht_operations.pco_phase =
			        (ie_data_bytes[5] & pco_phase_mask) ? PcoPhase::FourtyMhz : PcoPhase::TwentyMhz;
			//			ies.ht_operations.rx_mcs;
			//			ies.ht_operations.highest_supported_data_rate;
			//			ies.ht_operations.tx_mcs_defined;
			//			ies.ht_operations.tx_rx_mcs_equal;
			//			ies.ht_operations.tx_unequal_modulation;
			break;
		case WLAN_EID_VHT_CAPABILITY:
			if (element_data_length != vht_capability_data_length) {
				break;
			}
			ies.vht_capabilities.supported = true;
			break;
		case WLAN_EID_VHT_OPERATION:
			if (element_data_length != vht_operation_data_length) {
				break;
			}
			ies.vht_operations.supported = true;
			switch (ie_data_bytes[0]) {
			case 0:
				ies.vht_operations.channel_width = VhtChannelWidth::TwentyOrFortyMhz;
				break;
			case 1:
				ies.vht_operations.channel_width = VhtChannelWidth::EightyMhz;
				break;
			case 2:
				ies.vht_operations.channel_width = VhtChannelWidth::OneSixtyMhz;
				break;
			case 3:
				ies.vht_operations.channel_width = VhtChannelWidth::EightyPlusEightyMhz;
				break;
			}
			ies.vht_operations.channel_center_segment_zero =
			        static_cast<unsigned char>(ie_data_bytes[1]);
			ies.vht_operations.channel_center_segment_one =
			        static_cast<unsigned char>(ie_data_bytes[2]);
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
