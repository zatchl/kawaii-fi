#ifndef WPA_H
#define WPA_H

#include "libkawaii-fi/security.h"
#include "vendor_specific.h"

#include <QByteArray>
#include <QVector>
#include <array>
#include <string_view>

class QStandardItem;

namespace KawaiiFi::Ies {
	class Wpa : public VendorSpecific {
	public:
		Wpa() = default;
		explicit Wpa(const std::string_view &bytes);

		[[nodiscard]] QStandardItem *standard_item() const override;

		[[nodiscard]] unsigned int version() const;
		[[nodiscard]] KawaiiFi::Security::CipherSuite group_cipher_suite() const;
		[[nodiscard]] unsigned int pairwise_cipher_suite_count() const;
		[[nodiscard]] QVector<KawaiiFi::Security::CipherSuite> pairwise_cipher_suites() const;
		[[nodiscard]] unsigned int akm_suite_count() const;
		[[nodiscard]] QVector<KawaiiFi::Security::AkmSuite> akm_suites() const;

	private:
		[[nodiscard]] QByteArray::size_type akm_suites_start() const;
		[[nodiscard]] QByteArray::size_type wpa_capabilities_start() const;
	};

	inline const std::array<unsigned char, 3> WPA_OUI = {0x00, 0x50, 0xf2};
	inline const unsigned int WPA_VENDOR_TYPE = 1;
} // namespace KawaiiFi::Ies

#endif
