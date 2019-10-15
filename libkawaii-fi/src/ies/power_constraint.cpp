#include "libkawaii-fi/ies/power_constraint.h"

#include "libkawaii-fi/ies/information_element.h"
#include "standard-items/power_constraint_standard_item.h"

class QStandardItem;

namespace KawaiiFi::Ies {
	PowerConstraint::PowerConstraint(const std::string_view &bytes)
	    : InformationElement(bytes, WLAN_EID_PWR_CONSTRAINT)
	{
	}

	QStandardItem *PowerConstraint::standard_item() const
	{
		return new PowerConstraintStandardItem(*this);
	}

	QString PowerConstraint::summary() const
	{
		return QString("%0 dB").arg(local_power_constraint());
	}

	unsigned int PowerConstraint::local_power_constraint() const
	{
		constexpr unsigned int byte_index = 0;
		return byte_to_unsigned_int(byte_index);
	}
} // namespace KawaiiFi::Ies
