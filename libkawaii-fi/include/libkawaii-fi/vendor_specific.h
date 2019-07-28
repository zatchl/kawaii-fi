#ifndef VENDOR_SPECIFIC_H
#define VENDOR_SPECIFIC_H

#include "array"
#include "information_element.h"

class VendorSpecific : public InformationElement {
public:
	VendorSpecific() = default;
	VendorSpecific(const InformationElement &ie);

	std::array<unsigned char, 3> oui() const;
	unsigned int type() const;
};

inline const unsigned int WLAN_EID_VENDOR_SPECIFIC = 221;

#endif // VENDOR_SPECIFIC_H
