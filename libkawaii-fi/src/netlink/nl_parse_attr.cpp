#include "nl_parse_attr.h"

#include "libkawaii-fi/ies/country_info.h"
#include "libkawaii-fi/ies/ds_parameter.h"
#include "libkawaii-fi/ies/erp_info.h"
#include "libkawaii-fi/ies/extended_capabilities.h"
#include "libkawaii-fi/ies/ht_capabilities.h"
#include "libkawaii-fi/ies/ht_operations.h"
#include "libkawaii-fi/ies/information_element.h"
#include "libkawaii-fi/ies/power_constraint.h"
#include "libkawaii-fi/ies/rm_capabilities.h"
#include "libkawaii-fi/ies/robust_security_network.h"
#include "libkawaii-fi/ies/ssid.h"
#include "libkawaii-fi/ies/supported_rates.h"
#include "libkawaii-fi/ies/traffic_indication_map.h"
#include "libkawaii-fi/ies/variant.h"
#include "libkawaii-fi/ies/vendor_specific.h"
#include "libkawaii-fi/ies/vht_capabilities.h"
#include "libkawaii-fi/ies/vht_operations.h"
#include "libkawaii-fi/ies/wpa.h"

#include <QByteArray>
#include <algorithm>
#include <array>
#include <cstdint>
#include <libnl3/netlink/attr.h>
#include <linux/nl80211.h>
#include <string_view>

namespace KawaiiFi {
	QString parse_bssid(nlattr *attr)
	{
		if (attr == nullptr) {
			return "";
		}

		return QByteArray::fromRawData(nla_get_string(attr), nla_len(attr)).toHex(':').toUpper();
	}

	int parse_signal_strength_mbm(nlattr *attr)
	{
		if (attr == nullptr) {
			return 0;
		}

		return nla_get_s32(attr);
	}

	unsigned int parse_age_ms(nlattr *attr)
	{
		if (attr == nullptr) {
			return 0;
		}

		return 0;
	}

	ConnectionStatus parse_connection_status(nlattr *attr)
	{
		if (attr == nullptr) {
			return ConnectionStatus::Unknown;
		}

		switch (nla_get_u32(attr)) {
		case NL80211_BSS_STATUS_AUTHENTICATED:
			return ConnectionStatus::Authenticated;
		case NL80211_BSS_STATUS_ASSOCIATED:
			return ConnectionStatus::Associated;
		case NL80211_BSS_STATUS_IBSS_JOINED:
			return ConnectionStatus::IbssJoined;
		default:
			return ConnectionStatus::Unknown;
		}
	}

	unsigned int parse_frequency(nlattr *attr)
	{
		if (attr == nullptr) {
			return 0;
		}

		return nla_get_u32(attr);
	}

	unsigned int parse_tsf(nlattr *attr)
	{
		if (attr == nullptr) {
			return 0;
		}

		return 0;
	}

	unsigned int parse_beacon_interval(nlattr *attr)
	{
		if (attr == nullptr) {
			return 0;
		}

		return 0;
	}

	Capabilities parse_capabilities(nlattr *attr)
	{
		if (attr == nullptr) {
			return Capabilities();
		}

		return Capabilities(nla_get_string(attr), nla_len(attr));
	}

	QVector<Ies::Variant> parse_ies(nlattr *attr)
	{
		QVector<Ies::Variant> ies;

		if (attr == nullptr) {
			return ies;
		}

		const auto ies_bytes =
		        std::string_view(nla_get_string(attr), static_cast<unsigned int>(nla_len(attr)));

		// The index of each IE in ies_bytes
		std::string_view::size_type element_start = 0;
		// The length of the data portion of each IE
		std::string_view::size_type element_data_length = static_cast<std::uint8_t>(ies_bytes[1]);
		// The total length of each element
		std::string_view::size_type element_length = element_data_length + 2;

		while (element_start + element_length <= ies_bytes.size()) {
			// Element ID + Element Data Length + Element Data
			const std::string_view ie_bytes = ies_bytes.substr(element_start, element_length);
			// Only Element Data
			const std::string_view ie_data_bytes = ie_bytes.substr(2, element_data_length);
			// The Element ID
			const auto ie_id = static_cast<std::uint8_t>(ie_bytes[0]);

			switch (ie_id) {
			case Ies::WLAN_EID_COUNTRY:
				ies.append(Ies::CountryInfo(ie_data_bytes));
				break;
			case Ies::WLAN_EID_DS_PARAMS:
				ies.append(Ies::DsParameter(ie_data_bytes));
				break;
			case Ies::WLAN_EID_ERP_INFO:
				ies.append(Ies::ErpInfo(ie_data_bytes));
				break;
			case Ies::WLAN_EID_EXT_CAPABILITY:
				ies.append(Ies::ExtendedCapabilities(ie_data_bytes));
				break;
			case Ies::WLAN_EID_HT_CAPABILITY:
				ies.append(Ies::HtCapabilities(ie_data_bytes));
				break;
			case Ies::WLAN_EID_HT_OPERATION:
				ies.append(Ies::HtOperations(ie_data_bytes));
				break;
			case Ies::WLAN_EID_PWR_CONSTRAINT:
				ies.append(Ies::PowerConstraint(ie_data_bytes));
				break;
			case Ies::WLAN_EID_RRM_ENABLED_CAPABILITIES:
				ies.append(Ies::RmCapabilities(ie_data_bytes));
				break;
			case Ies::WLAN_EID_RSN:
				ies.append(Ies::RobustSecurityNetwork(ie_data_bytes));
				break;
			case Ies::WLAN_EID_SSID:
				ies.append(Ies::Ssid(ie_data_bytes));
				break;
			case Ies::WLAN_EID_SUPP_RATES:
			case Ies::WLAN_EID_EXT_SUPP_RATES:
				ies.append(Ies::SupportedRates(ie_data_bytes, ie_id));
				break;
			case Ies::WLAN_EID_TIM:
				ies.append(Ies::TrafficIndicationMap(ie_data_bytes));
				break;
			case Ies::WLAN_EID_VENDOR_SPECIFIC: {
				const Ies::VendorSpecific vendor_specific_ie(ie_data_bytes);
				if (vendor_specific_ie.oui() == Ies::WPA_OUI && vendor_specific_ie.type() == 1) {
					ies.append(Ies::Wpa(ie_data_bytes));
				} else {
					ies.append(vendor_specific_ie);
				}
				break;
			}
			case Ies::WLAN_EID_VHT_CAPABILITY:
				ies.append(Ies::VhtCapabilities(ie_data_bytes));
				break;
			case Ies::WLAN_EID_VHT_OPERATION:
				ies.append(Ies::VhtOperations(ie_data_bytes));
				break;
			default:
				ies.append(Ies::InformationElement(ie_data_bytes, ie_id));
			}

			// The next element starts right after the current element
			element_start += element_length;
			if ((element_start + 1) >= ies_bytes.size()) {
				break;
			}
			// The second byte in each element is the length of the data
			element_data_length = static_cast<std::uint8_t>(ies_bytes[element_start + 1]);
			// The length of the next element is equal to the data length + 2
			// The 2 comes from the element ID byte and the element data length byte
			element_length = element_data_length + 2;
		}

		return ies;
	}
} // namespace KawaiiFi
