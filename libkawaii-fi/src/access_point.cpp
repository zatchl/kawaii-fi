#include "libkawaii-fi/access_point.h"

#include "libkawaii-fi/channel.h"
#include "libkawaii-fi/util.h"

#include <QDBusArgument>
#include <QString>

ChannelWidth AccessPoint::channel_width() const
{
	if (information_elements.vht_operations.supported) {
		switch (information_elements.vht_operations.channel_width) {
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
	if (information_elements.ht_operations.supported &&
	    information_elements.ht_operations.secondary_channel_offset !=
	            SecondaryChannelOffset::NoSecondaryChannel) {
		return ChannelWidth::FortyMhz;
	}
	return ChannelWidth::TwentyMhz;
}

Channel AccessPoint::channel() const
{
	switch (channel_width()) {
	case ChannelWidth::TwentyMhz:
		return Channel(frequency - 10, frequency + 10);
	case ChannelWidth::TwentyTwoMhz:
		return Channel(frequency - 11, frequency + 11);
	case ChannelWidth::FortyMhz:
		for (const auto &channel : forty_mhz_channels) {
			if (channel.contains(frequency)) {
				return channel;
			}
		}
		break;
	case ChannelWidth::EightyMhz:
		for (const auto &channel : eighty_mhz_channels) {
			if (channel.contains(frequency)) {
				return channel;
			}
		}
		break;
	case ChannelWidth::OneSixtyMhz:
		for (const auto &channel : one_sixty_mhz_channels) {
			if (channel.contains(frequency)) {
				return channel;
			}
		}
		break;
	case ChannelWidth::EightyPlusEightyMhz: {
		Channel first_eighty_mhz_channel;
		Channel second_eighty_mhz_channel;
		for (const auto &channel : eighty_mhz_channels) {
			if (channel.contains(information_elements.vht_operations.channel_center_segment_zero) ||
			    channel.contains(information_elements.vht_operations.channel_center_segment_one)) {
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

QDBusArgument &operator<<(QDBusArgument &argument, const AccessPoint &ap)
{
	QVector<int> protocols;
	for (Protocol p : ap.protocols) {
		protocols.append(static_cast<int>(p));
	}
	argument.beginStructure();
	argument << ap.bssid << static_cast<int>(ap.status) << ap.signal_strength_mbm << ap.frequency
	         << ap.age_ms << protocols << ap.information_elements;
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, AccessPoint &ap)
{
	int status;
	QVector<int> protocols;
	argument.beginStructure();
	argument >> ap.bssid >> status >> ap.signal_strength_mbm >> ap.frequency >> ap.age_ms >>
	        protocols >> ap.information_elements;
	argument.endStructure();
	ap.status = static_cast<ConnectionStatus>(status);
	for (int i : protocols) {
		ap.protocols.append(static_cast<Protocol>(i));
	}
	return argument;
}

bool operator==(const AccessPoint &lhs, const AccessPoint &rhs) { return lhs.bssid == rhs.bssid; }

bool operator!=(const AccessPoint &lhs, const AccessPoint &rhs) { return !(lhs == rhs); }
