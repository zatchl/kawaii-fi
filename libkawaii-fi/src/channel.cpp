#include "libkawaii-fi/channel.h"

#include "libkawaii-fi/util.h"

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
	if (center > 2400 && center < 2500) {
		return Band::TwoPointFourGhz;
	} else if (center > 3650 && center < 3700) {
		return Band::ThreePointSixGhz;
	} else if (center > 4900 && center < 5000) {
		return Band::FourPointNineGhz;
	} else if (center > 5000 && center < 5900) {
		return Band::FiveGhz;
	} else if (center > 57240 && center < 70200) {
		return Band::SixtyGhz;
	}
	return Band::Unknown;
}
