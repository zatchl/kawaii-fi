#ifndef COUNTRY_INFORMATION_H
#define COUNTRY_INFORMATION_H

#include "information_element.h"

#include <QString>
#include <QVector>

enum class Environment { Indoor, Outdoor, Any };

struct ChannelPowerConstraint {
	const unsigned int first_channel_number = 0;
	const unsigned int number_of_channels = 0;
	const int max_transmit_power_dbm = 0;
};

class CountryInfo : public InformationElement {
public:
	CountryInfo() = default;
	CountryInfo(const InformationElement &ie);

	[[nodiscard]] QString country_code() const;
	[[nodiscard]] Environment environment() const;
	[[nodiscard]] QVector<ChannelPowerConstraint> channel_constraints() const;
};

inline const unsigned int WLAN_EID_COUNTRY = 7;

#endif // COUNTRY_INFORMATION_H