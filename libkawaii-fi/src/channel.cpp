#include "libkawaii-fi/channel.h"

#include "libkawaii-fi/util.h"

#include <QString>

namespace {
	const unsigned int two_point_four_ghz_min = 2400;
	const unsigned int two_point_four_ghz_max = 2500;

	const unsigned int three_point_six_ghz_min = 3650;
	const unsigned int three_point_six_ghz_max = 3700;

	const unsigned int four_point_nine_ghz_min = 4900;
	const unsigned int four_point_nine_ghz_max = 5000;

	const unsigned int five_ghz_min = 5000;
	const unsigned int five_ghz_max = 5900;

	const unsigned int sixty_ghz_min = 57240;
	const unsigned int sixty_ghz_max = 70200;
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

unsigned int Channel::start_mhz() const { return start_freq_; }

unsigned int Channel::end_mhz() const { return end_freq_; }

unsigned int Channel::center_mhz() const { return (start_freq_ + end_freq_) / 2; }

unsigned int Channel::width_mhz() const { return end_freq_ - start_freq_; }

unsigned int Channel::number() const
{
	return static_cast<unsigned int>(
	        ieee80211_frequency_to_channel(static_cast<int>(center_mhz())));
}

unsigned int Channel::start_mhz_two() const { return start_freq_two_; }

unsigned int Channel::end_mhz_two() const { return end_freq_two_; }

unsigned int Channel::center_mhz_two() const { return (start_freq_two_ + end_freq_two_) / 2; }

unsigned int Channel::width_mhz_two() const { return end_freq_two_ - end_freq_; }

unsigned int Channel::number_two() const
{
	return static_cast<unsigned int>(
	        ieee80211_frequency_to_channel(static_cast<int>(center_mhz_two())));
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
