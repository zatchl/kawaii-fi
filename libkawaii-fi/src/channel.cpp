#include "libkawaii-fi/channel.h"

#include "libkawaii-fi/util.h"

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
		_start_freq = start_freq_one;
		_end_freq = end_freq_one;
	}

	if (end_freq_two >= start_freq_two) {
		_start_freq_two = start_freq_two;
		_end_freq_two = end_freq_two;
	}
}

unsigned int Channel::start_mhz() const { return _start_freq; }

unsigned int Channel::end_mhz() const { return _end_freq; }

unsigned int Channel::center_mhz() const { return (_start_freq + _end_freq) / 2; }

unsigned int Channel::width_mhz() const { return _end_freq - _start_freq; }

unsigned int Channel::number() const
{
	return static_cast<unsigned int>(
	        ieee80211_frequency_to_channel(static_cast<int>(center_mhz())));
}

unsigned int Channel::start_mhz_two() const { return _start_freq_two; }

unsigned int Channel::end_mhz_two() const { return _end_freq_two; }

unsigned int Channel::center_mhz_two() const { return (_start_freq_two + _end_freq_two) / 2; }

unsigned int Channel::width_mhz_two() const { return _end_freq_two - _end_freq; }

unsigned int Channel::number_two() const
{
	return static_cast<unsigned int>(
	        ieee80211_frequency_to_channel(static_cast<int>(center_mhz_two())));
}

bool Channel::contains(unsigned int freq) const
{
	return ((freq >= _start_freq) && (freq <= _end_freq)) ||
	       ((freq >= _start_freq_two) && (freq <= _end_freq_two));
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
}
