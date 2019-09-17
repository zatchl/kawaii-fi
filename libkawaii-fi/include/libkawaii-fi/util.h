#ifndef UTIL_H
#define UTIL_H

#include <linux/nl80211.h>

// From linux/net/wireless/util.c
inline constexpr unsigned int ieee80211_frequency_to_channel(unsigned int freq)
{
	/* see 802.11 17.3.8.3.2 and Annex J */
	constexpr unsigned int channel_14_freq = 2484;
	if (freq == channel_14_freq) {
		return 14;
	}

	if (freq < channel_14_freq) {
		return (freq - 2407) / 5;
	}

	constexpr unsigned int four_point_nine_ghz_min = 4910;
	constexpr unsigned int four_point_nine_ghz_max = 4980;
	if (freq >= four_point_nine_ghz_min && freq <= four_point_nine_ghz_max) {
		return (freq - 4000) / 5;
	}

	constexpr unsigned int dmg_band_min = 45000;
	if (freq <= dmg_band_min) {
		return (freq - 5000) / 5;
	}

	constexpr unsigned int sixty_ghz_min = 58320;
	constexpr unsigned int sixty_ghz_max = 70200;
	if (freq >= sixty_ghz_min && freq <= sixty_ghz_max) {
		return (freq - 56160) / 2160;
	}

	return 0;
}

// From linux/net/wireless/util.c
inline constexpr unsigned int ieee80211_channel_to_frequency(unsigned int chan,
                                                             enum nl80211_band band)
{
	/* see 802.11 17.3.8.3.2 and Annex J
	 * there are overlapping channel numbers in 5GHz and 2GHz bands */
	switch (band) {
	case NL80211_BAND_2GHZ:
		if (chan == 14)
			return 2484;
		else if (chan < 14)
			return 2407 + chan * 5;
		break;
	case NL80211_BAND_5GHZ:
		if (chan >= 182 && chan <= 196) {
			return 4000 + chan * 5;
		}
		return 5000 + chan * 5;
	case NL80211_BAND_60GHZ:
		if (chan < 7) {
			return 56160 + chan * 2160;
		}
		break;
	default:;
	}
	return 0; /* not supported */
}

#endif // UTIL_H
