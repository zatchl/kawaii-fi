#ifndef CHANNEL_H
#define CHANNEL_H

#include <QVector>

enum class Band { TwoPointFourGhz, ThreePointSixGhz, FourPointNineGhz, FiveGhz, SixtyGhz, Unknown };

class Channel {
public:
	Channel(unsigned int start_freq, unsigned int end_freq);
	unsigned int start_mhz() const;
	unsigned int end_mhz() const;
	unsigned int center_mhz() const;
	unsigned int width_mhz() const;
	unsigned int number() const;
	bool contains(unsigned int freq) const;
	Band band() const;

private:
	unsigned int _start_freq = 0;
	unsigned int _end_freq = 0;
};

inline const QVector<Channel> forty_mhz_channels = {
        Channel(5150, 5190), Channel(5170, 5210), Channel(5210, 5250), Channel(5250, 5290),
        Channel(5290, 5330), Channel(5490, 5530), Channel(5530, 5570), Channel(5570, 5610),
        Channel(5610, 5650), Channel(5650, 5690), Channel(5690, 5730), Channel(5735, 5775),
        Channel(5775, 5815)};

inline const QVector<Channel> eighty_mhz_channels = {Channel(5170, 5250), Channel(5250, 5330),
                                                     Channel(5490, 5570), Channel(5570, 5650),
                                                     Channel(5650, 5730), Channel(5735, 5815)};

inline const QVector<Channel> one_sixty_mhz_channels = {Channel(5170, 5330), Channel(5490, 5650)};

#endif // CHANNEL_H
