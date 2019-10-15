#include "libkawaii-fi/channel.h"

#include "libkawaii-fi/ies/ht_operations.h"
#include "libkawaii-fi/ies/variant.h"
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

KawaiiFi::Channel::Channel(unsigned int start_freq, unsigned int end_freq)
    : Channel(start_freq, end_freq, 0, 0)
{
}

KawaiiFi::Channel::Channel(unsigned int start_freq_one, unsigned int end_freq_one,
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

KawaiiFi::Channel::Channel(unsigned int primary_center, const QVector<Ies::Variant> &ies)
{
	const Ies::HtOperations *ht_op = nullptr;
	const Ies::VhtOperations *vht_op = nullptr;

	for (const auto &ie : ies) {
		if (ht_op == nullptr) {
			ht_op = std::get_if<Ies::HtOperations>(&ie);
		}

		if (vht_op == nullptr) {
			vht_op = std::get_if<Ies::VhtOperations>(&ie);
		}
	}

	switch (Channel::width_from_ies(ies)) {
	case Width::TwentyMhz:
		start_freq_ = primary_center - 10;
		end_freq_ = primary_center + 10;
		break;
	case Width::TwentyTwoMhz:
		start_freq_ = primary_center - 11;
		start_freq_ = primary_center + 11;
		break;
	case Width::FortyMhz:
		if (ht_op != nullptr) {
			unsigned int channel_center = primary_center;
			channel_center +=
			        (ht_op->secondary_channel_offset() == Ies::SecondaryChannelOffset::Above)
			                ? 10U
			                : -10U;
			start_freq_ = channel_center - 20;
			end_freq_ = channel_center + 20;
		}
		break;
	case Width::EightyMhz:
		if (vht_op != nullptr) {
			unsigned int channel_center = ieee80211_channel_to_frequency(
			        vht_op->channel_center_segment_zero(), nl80211_band::NL80211_BAND_5GHZ);
			start_freq_ = channel_center - 40;
			end_freq_ = channel_center + 40;
		}
		break;
	case Width::EightyPlusEightyMhz:
		if (vht_op != nullptr) {
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
	case Width::OneSixtyMhz:
		if (vht_op != nullptr) {
			unsigned int channel_center = ieee80211_channel_to_frequency(
			        vht_op->channel_center_segment_zero(), nl80211_band::NL80211_BAND_5GHZ);
			start_freq_ = channel_center - 80;
			end_freq_ = channel_center + 80;
		}
		break;
	case Width::Other:
		break;
	}
}

unsigned int KawaiiFi::Channel::start_mhz() const { return start_freq_; }

unsigned int KawaiiFi::Channel::end_mhz() const { return end_freq_; }

unsigned int KawaiiFi::Channel::center_mhz() const { return (start_freq_ + end_freq_) / 2; }

unsigned int KawaiiFi::Channel::width_mhz() const { return end_freq_ - start_freq_; }

unsigned int KawaiiFi::Channel::number() const
{
	return ieee80211_frequency_to_channel(center_mhz());
}

unsigned int KawaiiFi::Channel::start_mhz_two() const { return start_freq_two_; }

unsigned int KawaiiFi::Channel::end_mhz_two() const { return end_freq_two_; }

unsigned int KawaiiFi::Channel::center_mhz_two() const
{
	return (start_freq_two_ + end_freq_two_) / 2;
}

unsigned int KawaiiFi::Channel::width_mhz_two() const { return end_freq_two_ - end_freq_; }

unsigned int KawaiiFi::Channel::number_two() const
{
	return ieee80211_frequency_to_channel(center_mhz_two());
}

bool KawaiiFi::Channel::contains(unsigned int freq) const
{
	return ((freq >= start_freq_) && (freq <= end_freq_)) ||
	       ((freq >= start_freq_two_) && (freq <= end_freq_two_));
}

KawaiiFi::Channel::Band KawaiiFi::Channel::band() const
{
	const unsigned int center = center_mhz();

	if (center > two_point_four_ghz_min && center < two_point_four_ghz_max) {
		return Band::TwoPointFourGhz;
	}

	if (center > three_point_six_ghz_min && center < three_point_six_ghz_max) {
		return Band::ThreePointSixGhz;
	}

	if (center > four_point_nine_ghz_min && center < four_point_nine_ghz_max) {
		return Band::FourPointNineGhz;
	}

	if (center > five_ghz_min && center < five_ghz_max) {
		return Band::FiveGhz;
	}

	if (center > sixty_ghz_min && center < sixty_ghz_max) {
		return Band::SixtyGhz;
	}

	return Band::Unknown;
}

KawaiiFi::Channel::Width KawaiiFi::Channel::width() const
{
	switch (width_mhz()) {
	case 20:
		return Width::TwentyMhz;
	case 22:
		return Width::TwentyTwoMhz;
	case 40:
		return Width::FortyMhz;
	case 80:
		return (width_mhz_two() == 80) ? Width::EightyPlusEightyMhz : Width::EightyMhz;
	case 160:
		return Width::OneSixtyMhz;
	}
	return Width::Other;
}

KawaiiFi::Channel::Width KawaiiFi::Channel::width_from_ies(const QVector<Ies::Variant> &ies)
{
	// Check for VHT Operation element
	auto vht_it = std::find_if(ies.begin(), ies.end(), [](const auto &ie) {
		return std::holds_alternative<Ies::VhtOperations>(ie);
	});

	if (vht_it != ies.end()) {
		switch (std::get<Ies::VhtOperations>(*vht_it).channel_width()) {
		case Ies::VhtChannelWidth::TwentyOrFortyMhz:
			break;
		case Ies::VhtChannelWidth::EightyMhz:
			return Width::EightyMhz;
		case Ies::VhtChannelWidth::OneSixtyMhz:
			return Width::OneSixtyMhz;
		case Ies::VhtChannelWidth::EightyPlusEightyMhz:
			return Width::EightyPlusEightyMhz;
		}
	}

	// Check for HT Operation element
	auto ht_it = std::find_if(ies.begin(), ies.end(), [](const auto &ie) {
		return std::holds_alternative<Ies::HtOperations>(ie);
	});

	if (ht_it != ies.end()) {
		return (std::get<Ies::HtOperations>(*ht_it).secondary_channel_offset() ==
		        Ies::SecondaryChannelOffset::NoSecondaryChannel)
		               ? Width::TwentyMhz
		               : Width::FortyMhz;
	}

	return Width::TwentyMhz;
}

QString KawaiiFi::Channel::width_to_string(Width channel_width)
{
	switch (channel_width) {
	case Width::TwentyMhz:
		return "20 MHz";
	case Width::TwentyTwoMhz:
		return "22 MHz";
	case Width::FortyMhz:
		return "40 MHz";
	case Width::EightyMhz:
		return "80 MHz";
	case Width::EightyPlusEightyMhz:
		return "80+80 MHz";
	case Width::OneSixtyMhz:
		return "160 MHz";
	default:
		return QString();
	}
}
