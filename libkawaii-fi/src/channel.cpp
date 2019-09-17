#include "libkawaii-fi/channel.h"

#include "libkawaii-fi/ies/ht_operations.h"
#include "libkawaii-fi/ies/ie_variant.h"
#include "libkawaii-fi/ies/vht_operations.h"
#include "libkawaii-fi/util.h"

#include <QString>
#include <algorithm>
#include <linux/nl80211.h>
#include <variant>

namespace {
	constexpr unsigned int two_point_four_ghz_min = 2400;
	constexpr unsigned int two_point_four_ghz_max = 2500;

	constexpr unsigned int three_point_six_ghz_min = 3650;
	constexpr unsigned int three_point_six_ghz_max = 3700;

	constexpr unsigned int four_point_nine_ghz_min = 4900;
	constexpr unsigned int four_point_nine_ghz_max = 5000;

	constexpr unsigned int five_ghz_min = 5000;
	constexpr unsigned int five_ghz_max = 5900;

	constexpr unsigned int sixty_ghz_min = 57240;
	constexpr unsigned int sixty_ghz_max = 70200;
} // namespace

Channel::Channel(unsigned int start_freq, unsigned int end_freq)
    : Channel(start_freq, end_freq, 0, 0)
{
}

Channel::Channel(unsigned int start_freq_one, unsigned int end_freq_one,
                 unsigned int start_freq_two, unsigned int end_freq_two)
{
	if (end_freq_one >= start_freq_one) {
		start_freq_ = start_freq_one;
		end_freq_ = end_freq_one;
	}

	if (end_freq_two >= start_freq_two) {
		start_freq_two_ = start_freq_two;
		end_freq_two_ = end_freq_two;
	}
}

Channel::Channel(unsigned int primary_center, const QVector<IeVariant> &ies)
{
	const HtOperations *ht_op = nullptr;
	const VhtOperations *vht_op = nullptr;

	for (const auto &ie : ies) {
		if (!ht_op) {
			ht_op = std::get_if<HtOperations>(&ie);
		}

		if (!vht_op) {
			vht_op = std::get_if<VhtOperations>(&ie);
		}
	}

	switch (Channel::width_from_ies(ies)) {
	case ChannelWidth::TwentyMhz:
		start_freq_ = primary_center - 10;
		end_freq_ = primary_center + 10;
		break;
	case ChannelWidth::TwentyTwoMhz:
		start_freq_ = primary_center - 11;
		start_freq_ = primary_center + 11;
		break;
	case ChannelWidth::FortyMhz:
		if (ht_op) {
			unsigned int channel_center = primary_center;
			channel_center += (ht_op->secondary_channel_offset() == SecondaryChannelOffset::Above)
			                          ? 10U
			                          : -10U;
			start_freq_ = channel_center - 20;
			end_freq_ = channel_center + 20;
		}
		break;
	case ChannelWidth::EightyMhz:
		if (vht_op) {
			unsigned int channel_center = ieee80211_channel_to_frequency(
			        vht_op->channel_center_segment_zero(), nl80211_band::NL80211_BAND_5GHZ);
			start_freq_ = channel_center - 40;
			end_freq_ = channel_center + 40;
		}
		break;
	case ChannelWidth::EightyPlusEightyMhz:
		if (vht_op) {
			unsigned int channel_center_zero = ieee80211_channel_to_frequency(
			        vht_op->channel_center_segment_zero(), nl80211_band::NL80211_BAND_5GHZ);
			start_freq_ = channel_center_zero - 40;
			end_freq_ = channel_center_zero + 40;
			unsigned int channel_center_one = ieee80211_channel_to_frequency(
			        vht_op->channel_center_segment_one(), nl80211_band::NL80211_BAND_5GHZ);
			start_freq_two_ = channel_center_one - 40;
			end_freq_two_ = channel_center_one + 40;
		}
		break;
	case ChannelWidth::OneSixtyMhz:
		if (vht_op) {
			unsigned int channel_center = ieee80211_channel_to_frequency(
			        vht_op->channel_center_segment_zero(), nl80211_band::NL80211_BAND_5GHZ);
			start_freq_ = channel_center - 80;
			end_freq_ = channel_center + 80;
		}
		break;
	case ChannelWidth::Other:
		break;
	}
}

unsigned int Channel::start_mhz() const { return start_freq_; }

unsigned int Channel::end_mhz() const { return end_freq_; }

unsigned int Channel::center_mhz() const { return (start_freq_ + end_freq_) / 2; }

unsigned int Channel::width_mhz() const { return end_freq_ - start_freq_; }

unsigned int Channel::number() const { return ieee80211_frequency_to_channel(center_mhz()); }

unsigned int Channel::start_mhz_two() const { return start_freq_two_; }

unsigned int Channel::end_mhz_two() const { return end_freq_two_; }

unsigned int Channel::center_mhz_two() const { return (start_freq_two_ + end_freq_two_) / 2; }

unsigned int Channel::width_mhz_two() const { return end_freq_two_ - end_freq_; }

unsigned int Channel::number_two() const
{
	return ieee80211_frequency_to_channel(center_mhz_two());
}

bool Channel::contains(unsigned int freq) const
{
	return ((freq >= start_freq_) && (freq <= end_freq_)) ||
	       ((freq >= start_freq_two_) && (freq <= end_freq_two_));
}

WifiBand Channel::band() const
{
	const unsigned int center = center_mhz();

	if (center > two_point_four_ghz_min && center < two_point_four_ghz_max) {
		return WifiBand::TwoPointFourGhz;
	}

	if (center > three_point_six_ghz_min && center < three_point_six_ghz_max) {
		return WifiBand::ThreePointSixGhz;
	}

	if (center > four_point_nine_ghz_min && center < four_point_nine_ghz_max) {
		return WifiBand::FourPointNineGhz;
	}

	if (center > five_ghz_min && center < five_ghz_max) {
		return WifiBand::FiveGhz;
	}

	if (center > sixty_ghz_min && center < sixty_ghz_max) {
		return WifiBand::SixtyGhz;
	}

	return WifiBand::Unknown;
}

ChannelWidth Channel::width() const
{
	switch (width_mhz()) {
	case 20:
		return ChannelWidth::TwentyMhz;
	case 22:
		return ChannelWidth::TwentyTwoMhz;
	case 40:
		return ChannelWidth::FortyMhz;
	case 80:
		return (width_mhz_two() == 80) ? ChannelWidth::EightyPlusEightyMhz
		                               : ChannelWidth::EightyMhz;
	case 160:
		return ChannelWidth::OneSixtyMhz;
	}
	return ChannelWidth::Other;
}

ChannelWidth Channel::width_from_ies(const QVector<IeVariant> &ies)
{
	// Check for VHT Operation element
	auto vht_it = std::find_if(ies.begin(), ies.end(), [](const auto &ie) {
		return std::holds_alternative<VhtOperations>(ie);
	});

	if (vht_it != ies.end()) {
		switch (std::get<VhtOperations>(*vht_it).channel_width()) {
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

	// Check for HT Operation element
	auto ht_it = std::find_if(ies.begin(), ies.end(), [](const auto &ie) {
		return std::holds_alternative<HtOperations>(ie);
	});

	if (ht_it != ies.end()) {
		return (std::get<HtOperations>(*ht_it).secondary_channel_offset() ==
		        SecondaryChannelOffset::NoSecondaryChannel)
		               ? ChannelWidth::TwentyMhz
		               : ChannelWidth::FortyMhz;
	}

	return ChannelWidth::TwentyMhz;
}

QString channel_width_to_string(ChannelWidth channel_width)
{
	switch (channel_width) {
	case ChannelWidth::TwentyMhz:
		return "20 MHz";
	case ChannelWidth::TwentyTwoMhz:
		return "22 MHz";
	case ChannelWidth::FortyMhz:
		return "40 MHz";
	case ChannelWidth::EightyMhz:
		return "80 MHz";
	case ChannelWidth::EightyPlusEightyMhz:
		return "80+80 MHz";
	case ChannelWidth::OneSixtyMhz:
		return "160 MHz";
	default:
		return QString();
	}
}
