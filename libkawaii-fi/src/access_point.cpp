#include "libkawaii-fi/access_point.h"

#include "libkawaii-fi/channel.h"
#include "libkawaii-fi/ht_operations.h"
#include "libkawaii-fi/information_elements.h"
#include "libkawaii-fi/vht_operations.h"

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

const InformationElements &AccessPoint::information_elements() const
{
	return information_elements_;
}

InformationElements &AccessPoint::information_elements() { return information_elements_; }

ChannelWidth AccessPoint::channel_width() const
{
	if (information_elements_.vht_operations.supported()) {
		switch (information_elements_.vht_operations.channel_width()) {
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
	if (information_elements_.ht_operations.supported() &&
	    information_elements_.ht_operations.secondary_channel_offset() !=
	            SecondaryChannelOffset::NoSecondaryChannel) {
		return ChannelWidth::FortyMhz;
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
		for (const auto &channel : eighty_mhz_channels) {
			if (channel.contains(
			            information_elements_.vht_operations.channel_center_segment_zero()) ||
			    channel.contains(
			            information_elements_.vht_operations.channel_center_segment_one())) {
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

void AccessPoint::set_protocols(const QVector<Protocol> &protocols) { protocols_ = protocols; }

void AccessPoint::set_information_elements(const InformationElements &information_elements)
{
	information_elements_ = information_elements;
}

QDBusArgument &operator<<(QDBusArgument &argument, const AccessPoint &ap)
{
	QVector<int> protocols;
	for (Protocol p : ap.protocols()) {
		protocols.append(static_cast<int>(p));
	}
	argument.beginStructure();
	argument << ap.bssid() << static_cast<int>(ap.connection_status()) << ap.signal_strength_mbm()
	         << ap.frequency() << ap.age_ms() << protocols << ap.information_elements();
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
	ap.set_information_elements(qdbus_cast<InformationElements>(argument));
	argument.endStructure();
	return argument;
}

bool operator==(const AccessPoint &lhs, const AccessPoint &rhs)
{
	return lhs.bssid() == rhs.bssid();
}

bool operator!=(const AccessPoint &lhs, const AccessPoint &rhs) { return !(lhs == rhs); }
