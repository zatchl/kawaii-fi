#include "libkawaii-fi/ies/power_constraint.h"

#include "libkawaii-fi/ies/information_element.h"

#include <QByteArray>
#include <cstdint>

PowerConstraint::PowerConstraint(const InformationElement &ie) : InformationElement(ie.bytes()) {}

unsigned int PowerConstraint::local_power_constraint() const
{
	constexpr unsigned int byte_index = 0;
	return byte_to_unsigned_int(byte_index);
}
