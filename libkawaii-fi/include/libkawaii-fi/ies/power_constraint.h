#ifndef POWER_CONSTRAINT_H
#define POWER_CONSTRAINT_H

#include "information_element.h"

#include <QString>
#include <string_view>

class QStandardItem;

namespace KawaiiFi::Ies {
	class PowerConstraint : public InformationElement {
	public:
		PowerConstraint() = default;
		explicit PowerConstraint(const std::string_view &bytes);

		[[nodiscard]] QStandardItem *standard_item() const override;
		[[nodiscard]] QString summary() const override;

		[[nodiscard]] unsigned int local_power_constraint() const;
	};

	inline const unsigned int WLAN_EID_PWR_CONSTRAINT = 32;
} // namespace KawaiiFi::Ies

#endif // POWER_CONSTRAINT_H
