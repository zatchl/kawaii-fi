#ifndef WPA_H
#define WPA_H

#include "libkawaii-fi/security.h"
#include "vendor_specific.h"

#include <QVector>
#include <array>

class Wpa : public VendorSpecific {
public:
	Wpa() = default;
	Wpa(const VendorSpecific &vs);

	[[nodiscard]] unsigned int version() const;
	[[nodiscard]] CipherSuite group_cipher_suite() const;
	[[nodiscard]] unsigned int pairwise_cipher_suite_count() const;
	[[nodiscard]] QVector<CipherSuite> pairwise_cipher_suites() const;
	[[nodiscard]] unsigned int akm_suite_count() const;
	[[nodiscard]] QVector<AkmSuite> akm_suites() const;

private:
	[[nodiscard]] unsigned int pairwise_cipher_suites_start() const;
	[[nodiscard]] unsigned int akm_suites_start() const;
	[[nodiscard]] unsigned int wpa_capabilities_start() const;
};

inline const std::array<unsigned char, 3> WPA_OUI = {0x00, 0x50, 0xf2};
inline const unsigned int WPA_VENDOR_TYPE = 1;

#endif
