#include "nl_wifi_parse.h"

#include "ieee80211.h"

#include <QByteArray>
#include <QString>
#include <libnl3/netlink/attr.h>
#include <libnl3/netlink/data.h>

QString KawaiiFi::parse_bssid(nlattr *bssid_attr)
{
	return QByteArray::fromRawData(nla_get_string(bssid_attr), nla_len(bssid_attr)).toHex(':');
}

unsigned int KawaiiFi::parse_frequency(nlattr *frequency_attr)
{
	return nla_get_u32(frequency_attr);
}

{

KawaiiFi::InformationElements KawaiiFi::parse_information_elements(nlattr *ies_attr)
{
	InformationElements ie;
	const auto ies_bytes = QByteArray::fromRawData(nla_get_string(ies_attr), nla_len(ies_attr));
	QByteArray::const_iterator element = ies_bytes.cbegin();
	while (element + 1 < ies_bytes.cend()) {
		// The second byte in each information element contains the length of the data
		int data_length = static_cast<unsigned char>(*(element + 1));
		if (element + 1 + data_length >= ies_bytes.cend()) {
			break;
		}

		// The first byte in each information element contains the element's ID
		switch (static_cast<unsigned char>(*element)) {
		case WLAN_EID_SSID:
			// The length of the SSID is between 0 and 32 bytes
			if (data_length <= 32) {
				ie.ssid = QString::fromLocal8Bit(element + 2, data_length);
			}
			break;
		case WLAN_EID_SUPP_RATES:
		case WLAN_EID_EXT_SUPP_RATES:
			for (auto i = element + 2; i < element + 2 + data_length; ++i) {
				auto rate_byte = static_cast<unsigned char>(*i);

				// The seven low-order bits encode the rate as a multiple of 500 kbps, therefore we
				// divide by 2 to convert to mbps
				int rate_mbps = (rate_byte & 0x7f) / 2;
				ie.supported_rates.append(rate_mbps);

				// The most significant bit of the rate byte indicates whether the rate is
				// basic/mandatory or not
				if (rate_byte & 0x80) {
					ie.basic_rates.append(rate_mbps);
				}
			}
			break;
		case WLAN_EID_DS_PARAMS:
			if (data_length == 1) {
				ie.channel = static_cast<unsigned char>(*(element + 2));
			}
			break;
		}
		// Increment the element iterator to the start of the next element
		element += data_length + 2;
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
