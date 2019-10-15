#ifndef CHANNEL_H
#define CHANNEL_H

#include "libkawaii-fi/ies/variant.h"

#include <QVector>

namespace KawaiiFi {
	class Channel {
	public:
		enum class Band {
			TwoPointFourGhz,
			ThreePointSixGhz,
			FourPointNineGhz,
			FiveGhz,
			SixtyGhz,
			Unknown
		};

		enum class Width {
			TwentyMhz,
			TwentyTwoMhz,
			FortyMhz,
			EightyMhz,
			OneSixtyMhz,
			EightyPlusEightyMhz,
			Other
		};

		Channel() = default;
		Channel(unsigned int start_freq, unsigned int end_freq);
		Channel(unsigned int start_freq_one, unsigned int end_freq_one, unsigned int start_freq_two,
		        unsigned int end_freq_two);
		Channel(unsigned int primary_center, const QVector<Ies::Variant> &ies);
		[[nodiscard]] unsigned int start_mhz() const;
		[[nodiscard]] unsigned int end_mhz() const;
		[[nodiscard]] unsigned int center_mhz() const;
		[[nodiscard]] unsigned int width_mhz() const;
		[[nodiscard]] unsigned int number() const;
		[[nodiscard]] unsigned int start_mhz_two() const;
		[[nodiscard]] unsigned int end_mhz_two() const;
		[[nodiscard]] unsigned int center_mhz_two() const;
		[[nodiscard]] unsigned int width_mhz_two() const;
		[[nodiscard]] unsigned int number_two() const;
		[[nodiscard]] bool contains(unsigned int freq) const;
		[[nodiscard]] Band band() const;
		[[nodiscard]] Width width() const;
		[[nodiscard]] static Width width_from_ies(const QVector<Ies::Variant> &ies);
		[[nodiscard]] static QString width_to_string(Width channel_width);

	private:
		unsigned int start_freq_ = 0;
		unsigned int end_freq_ = 0;
		unsigned int start_freq_two_ = 0;
		unsigned int end_freq_two_ = 0;
	};

	inline const QVector<Channel> forty_mhz_channels = {
	        Channel(5150, 5190), Channel(5170, 5210), Channel(5210, 5250), Channel(5250, 5290),
	        Channel(5290, 5330), Channel(5490, 5530), Channel(5530, 5570), Channel(5570, 5610),
	        Channel(5610, 5650), Channel(5650, 5690), Channel(5690, 5730), Channel(5735, 5775),
	        Channel(5775, 5815)};

	inline const QVector<Channel> eighty_mhz_channels = {Channel(5170, 5250), Channel(5250, 5330),
	                                                     Channel(5490, 5570), Channel(5570, 5650),
	                                                     Channel(5650, 5730), Channel(5735, 5815)};

	inline const QVector<Channel> one_sixty_mhz_channels = {Channel(5170, 5330),
	                                                        Channel(5490, 5650)};

} // namespace KawaiiFi

#endif // CHANNEL_H
