#ifndef RM_CAPABILITIES_H
#define RM_CAPABILITIES_H

#include "information_element.h"

#include <string_view>

class QStandardItem;

class RmCapabilities : public InformationElement {
public:
	RmCapabilities() = default;
	explicit RmCapabilities(const std::string_view &bytes);

	[[nodiscard]] QStandardItem *standard_item() const override;
};

inline const unsigned int WLAN_EID_RRM_ENABLED_CAPABILITIES = 70;

#endif // RM_CAPABILITIES_H
