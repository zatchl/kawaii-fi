#ifndef SSID_H
#define SSID_H

#include "information_element.h"

#include <QString>
#include <string_view>

class QStandardItem;

namespace KawaiiFi::Ies {
	class Ssid : public InformationElement {
	public:
		Ssid() = default;
		explicit Ssid(const std::string_view &bytes);

		[[nodiscard]] QStandardItem *standard_item() const override;
		[[nodiscard]] QString summary() const override;
	};

	inline const unsigned int WLAN_EID_SSID = 0;
} // namespace KawaiiFi::Ies

#endif // SSID_H
