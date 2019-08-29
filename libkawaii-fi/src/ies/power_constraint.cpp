#include "libkawaii-fi/ies/power_constraint.h"

#include "libkawaii-fi/ies/information_element.h"

#include <QByteArray>
#include <cstdint>

PowerConstraint::PowerConstraint(const InformationElement &ie) : InformationElement(ie.bytes()) {}

unsigned int PowerConstraint::local_power_constraint() const
{
	if (bytes().size() > 1) {
		return 0;
	}
	return static_cast<std::uint8_t>(bytes()[0]);
}
