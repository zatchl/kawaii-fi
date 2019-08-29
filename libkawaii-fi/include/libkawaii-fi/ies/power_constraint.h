#ifndef POWER_CONSTRAINT_H
#define POWER_CONSTRAINT_H

#include "information_element.h"

class PowerConstraint : public InformationElement {
public:
	PowerConstraint() = default;
	PowerConstraint(const InformationElement &ie);

	[[nodiscard]] unsigned int local_power_constraint() const;
};

inline const unsigned int WLAN_EID_PWR_CONSTRAINT = 32;

#endif // POWER_CONSTRAINT_H
