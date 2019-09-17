#include "libkawaii-fi/ies/power_constraint.h"

#include "libkawaii-fi/ies/information_element.h"
#include "standard-items/power_constraint_standard_item.h"

#include <QByteArray>
#include <cstdint>
class QStandardItem;

PowerConstraint::PowerConstraint(const InformationElement &ie) : InformationElement(ie.bytes()) {}

QStandardItem *PowerConstraint::standard_item() const
{
	return new PowerConstraintStandardItem(*this);
}

QString PowerConstraint::summary() const { return QString("%0 dB").arg(local_power_constraint()); }

unsigned int PowerConstraint::local_power_constraint() const
{
	constexpr unsigned int byte_index = 0;
	return byte_to_unsigned_int(byte_index);
}
