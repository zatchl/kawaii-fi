#include "libkawaii-fi/access_point.h"

#include "libkawaii-fi/capabilities.h"
#include "libkawaii-fi/channel.h"
#include "libkawaii-fi/ht_operations.h"
#include "libkawaii-fi/information_element.h"
#include "libkawaii-fi/robust_security_network.h"
#include "libkawaii-fi/vendor_specific.h"
#include "libkawaii-fi/vht_operations.h"
#include "libkawaii-fi/wpa.h"

#include <QList>
#include <algorithm>
#include <array>

const QString &AccessPoint::bssid() const { return bssid_; }

ConnectionStatus AccessPoint::connection_status() const { return connection_status_; }

int AccessPoint::signal_strength_mbm() const { return signal_strength_mbm_; }

double AccessPoint::signal_strength_dbm() const
{
	const int mbm_per_dbm = 100;
	return static_cast<double>(signal_strength_mbm_) / mbm_per_dbm;
}

unsigned int AccessPoint::frequency() const { return frequency_; }

unsigned int AccessPoint::age_ms() const { return age_ms_; }

const QVector<Protocol> &AccessPoint::protocols() const { return protocols_; }

QVector<Protocol> &AccessPoint::protocols() { return protocols_; }

const Capabilities &AccessPoint::capabilities() const { return capabilities_; }

Capabilities &AccessPoint::capabilites() { return capabilities_; }

const QMultiHash<unsigned int, InformationElement> &AccessPoint::information_elements() const
{
	return information_elements_;
}

QMultiHash<unsigned int, InformationElement> &AccessPoint::information_elements()
{
	return information_elements_;
}

bool AccessPoint::contains_vendor_element(const std::array<unsigned char, 3> &oui,
                                          unsigned int type) const
{
	for (auto &ie : information_elements_.values(WLAN_EID_VENDOR_SPECIFIC)) {
		const VendorSpecific v_ie = VendorSpecific(ie);
		if (v_ie.oui() == oui && v_ie.type() == type) {
			return true;
		}
	}
	return false;
}

ChannelWidth AccessPoint::channel_width() const
{
	if (information_elements_.contains(WLAN_EID_VHT_OPERATION)) {
		const VhtOperations &vht_operations = information_elements_.value(WLAN_EID_VHT_OPERATION);
		switch (vht_operations.channel_width()) {
		case VhtChannelWidth::TwentyOrFortyMhz:
			break;
		case VhtChannelWidth::EightyMhz:
			return ChannelWidth::EightyMhz;
		case VhtChannelWidth::OneSixtyMhz:
			return ChannelWidth::OneSixtyMhz;
		case VhtChannelWidth::EightyPlusEightyMhz:
			return ChannelWidth::EightyPlusEightyMhz;
		}
	}
	if (information_elements_.contains(WLAN_EID_HT_OPERATION)) {
		const HtOperations &ht_operations = information_elements_.value(WLAN_EID_HT_OPERATION);
		if (ht_operations.secondary_channel_offset() !=
		    SecondaryChannelOffset::NoSecondaryChannel) {
			return ChannelWidth::FortyMhz;
		}
	}
	return ChannelWidth::TwentyMhz;
}

Channel AccessPoint::channel() const
{
	switch (channel_width()) {
	case ChannelWidth::TwentyMhz:
		return Channel(frequency_ - 10, frequency_ + 10);
	case ChannelWidth::TwentyTwoMhz:
		return Channel(frequency_ - 11, frequency_ + 11);
	case ChannelWidth::FortyMhz:
		for (const auto &channel : forty_mhz_channels) {
			if (channel.contains(frequency_)) {
				return channel;
			}
		}
		break;
	case ChannelWidth::EightyMhz:
		for (const auto &channel : eighty_mhz_channels) {
			if (channel.contains(frequency_)) {
				return channel;
			}
		}
		break;
	case ChannelWidth::OneSixtyMhz:
		for (const auto &channel : one_sixty_mhz_channels) {
			if (channel.contains(frequency_)) {
				return channel;
			}
		}
		break;
	case ChannelWidth::EightyPlusEightyMhz: {
		Channel first_eighty_mhz_channel;
		Channel second_eighty_mhz_channel;
		if (!information_elements_.contains(WLAN_EID_VHT_OPERATION)) {
			break;
		}
		const VhtOperations &vht_operations = information_elements_.value(WLAN_EID_VHT_OPERATION);
		for (const auto &channel : eighty_mhz_channels) {
			if (channel.contains(vht_operations.channel_center_segment_zero()) ||
			    channel.contains(vht_operations.channel_center_segment_one())) {
				if (first_eighty_mhz_channel.center_mhz() == 0) {
					first_eighty_mhz_channel = channel;
				} else {
					second_eighty_mhz_channel = channel;
				}
			}
		}
		return Channel(first_eighty_mhz_channel.start_mhz(), first_eighty_mhz_channel.end_mhz(),
		               second_eighty_mhz_channel.start_mhz(), second_eighty_mhz_channel.end_mhz());
	}
	case ChannelWidth::Other:
		break;
	}
	return Channel();
}

QVector<Security> AccessPoint::security() const
{
	if (!capabilities_.privacy()) {
		return {Security::None};
	}

	const bool contains_wpa_ie = contains_vendor_element(WPA_OUI, WPA_VENDOR_TYPE);

	if (!information_elements_.contains(WLAN_EID_RSN) && !contains_wpa_ie) {
		return {Security::WEP};
	}

	QVector<Security> security;

	if (contains_wpa_ie) {
		security.append(Security::WPA);
	}

	if (information_elements_.contains(WLAN_EID_RSN)) {
		security.append(Security::WPA2);
	}

	return security;
}

void AccessPoint::set_bssid(const QString &bssid) { bssid_ = bssid; }

void AccessPoint::set_connection_status(ConnectionStatus connection_status)
{
	connection_status_ = connection_status;
}

void AccessPoint::set_signal_strength_mbm(int signal_strength_mbm)
{
	signal_strength_mbm_ = signal_strength_mbm;
}

void AccessPoint::set_frequency(unsigned int frequency) { frequency_ = frequency; }

void AccessPoint::set_age_ms(unsigned int age_ms) { age_ms_ = age_ms; }

void AccessPoint::set_capabilities(const char *bytes, int size)
{
	capabilities_ = Capabilities(bytes, size);
}

void AccessPoint::set_protocols(const QVector<Protocol> &protocols) { protocols_ = protocols; }

QDBusArgument &operator<<(QDBusArgument &argument, const AccessPoint &ap)
{
	QVector<int> protocols;
	for (Protocol p : ap.protocols()) {
		protocols.append(static_cast<int>(p));
	}
	argument.beginStructure();
	argument << ap.bssid() << static_cast<int>(ap.connection_status()) << ap.signal_strength_mbm()
	         << ap.frequency() << ap.age_ms() << protocols << ap.capabilities()
	         << ap.information_elements();
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, AccessPoint &ap)
{
	argument.beginStructure();
	ap.set_bssid(qdbus_cast<QString>(argument));
	ap.set_connection_status(static_cast<ConnectionStatus>(qdbus_cast<int>(argument)));
	ap.set_signal_strength_mbm(qdbus_cast<int>(argument));
	ap.set_frequency(qdbus_cast<unsigned int>(argument));
	ap.set_age_ms(qdbus_cast<unsigned int>(argument));
	for (int i : qdbus_cast<QVector<int>>(argument)) {
		ap.protocols().append(static_cast<Protocol>(i));
	}
	argument >> ap.capabilites();
	argument >> ap.information_elements();
	argument.endStructure();
	return argument;
}

bool operator==(const AccessPoint &lhs, const AccessPoint &rhs)
{
	return lhs.bssid() == rhs.bssid();
}

bool operator!=(const AccessPoint &lhs, const AccessPoint &rhs) { return !(lhs == rhs); }
