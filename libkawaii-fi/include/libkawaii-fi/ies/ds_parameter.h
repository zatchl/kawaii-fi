#ifndef DS_PARAMETER_H
#define DS_PARAMETER_H

#include "information_element.h"

#include <QString>
#include <string_view>

class QStandardItem;

namespace KawaiiFi::Ies {
	class DsParameter : public InformationElement {
	public:
		DsParameter() = default;
		explicit DsParameter(const std::string_view &bytes);

		[[nodiscard]] QStandardItem *standard_item() const override;
		[[nodiscard]] QString summary() const override;

		[[nodiscard]] unsigned int channel() const;
	};

	inline const unsigned int WLAN_EID_DS_PARAMS = 3;
} // namespace KawaiiFi::Ies

#endif // DS_PARAMETER_H
