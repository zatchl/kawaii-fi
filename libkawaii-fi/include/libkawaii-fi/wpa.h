#ifndef WPA_H
#define WPA_H

#include "vendor_specific.h"

#include <array>

class Wpa : public VendorSpecific {
	Wpa() = default;
	Wpa(const VendorSpecific &vs);
};

inline const std::array<unsigned char, 3> WPA_OUI = {0x00, 0x50, 0xf2};
inline const unsigned int WPA_VENDOR_TYPE = 1;

#endif
