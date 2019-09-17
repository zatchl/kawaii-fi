#ifndef VENDOR_SPECIFIC_H
#define VENDOR_SPECIFIC_H

#include "array"
#include "information_element.h"

#include <string_view>

class QStandardItem;

class VendorSpecific : public InformationElement {
public:
	VendorSpecific() = default;
	explicit VendorSpecific(const std::string_view &bytes);

	[[nodiscard]] QStandardItem *standard_item() const override;

	[[nodiscard]] std::array<unsigned char, 3> oui() const;
	[[nodiscard]] unsigned int type() const;
};

inline const unsigned int WLAN_EID_VENDOR_SPECIFIC = 221;

#endif // VENDOR_SPECIFIC_H
