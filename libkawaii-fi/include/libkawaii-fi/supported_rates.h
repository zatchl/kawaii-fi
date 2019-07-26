#ifndef SUPPORTED_RATES_H
#define SUPPORTED_RATES_H

#include "information_element.h"

#include <QSet>

class SupportedRates : public InformationElement {
public:
	SupportedRates() = default;
	SupportedRates(const InformationElement &ie);

	[[nodiscard]] QSet<double> basic_rates() const;
	[[nodiscard]] QSet<double> rates() const;
};

inline const unsigned int WLAN_EID_SUPP_RATES = 1;
inline const unsigned int WLAN_EID_EXT_SUPP_RATES = 50;

#endif // SUPPORTED_RATES_H
