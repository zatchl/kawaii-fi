#include "libkawaii-fi/ies/wpa.h"

#include "libkawaii-fi/ies/vendor_specific.h"

#include <QByteArray>
#include <QStandardItem>
#include <cstdint>

namespace {
	constexpr QByteArray::size_type pairwise_cipher_suites_start = 12;
} // namespace

namespace KawaiiFi::Ies {
	Wpa::Wpa(const std::string_view &bytes) : VendorSpecific(bytes) {}

	QStandardItem *Wpa::standard_item() const
	{
		auto standard_item = new QStandardItem("WPA");
		return standard_item;
	}

	unsigned int Wpa::version() const
	{
		if (bytes().size() < 6) {
			return 1;
		}
		return bytes()[4] + (static_cast<std::uint8_t>(bytes()[5]) << 8U);
	}

	KawaiiFi::Security::CipherSuite Wpa::group_cipher_suite() const
	{
		constexpr int oui_first_byte_index = 6;
		constexpr int oui_second_byte_index = 7;
		constexpr int oui_third_byte_index = 8;
		constexpr int suite_type_byte_index = 9;

		if (bytes().size() <= suite_type_byte_index) {
			return KawaiiFi::Security::CipherSuite();
		}

		std::array<std::uint8_t, 3> oui = {
		        static_cast<std::uint8_t>(bytes()[oui_first_byte_index]),
		        static_cast<std::uint8_t>(bytes()[oui_second_byte_index]),
		        static_cast<std::uint8_t>(bytes()[oui_third_byte_index])};
		switch (bytes()[suite_type_byte_index]) {
		case 1:
			return {oui, KawaiiFi::Security::CipherSuiteType::WEP40};
		case 2:
			return {oui, KawaiiFi::Security::CipherSuiteType::TKIP};
		case 5:
			return {oui, KawaiiFi::Security::CipherSuiteType::WEP104};
		default:
			return {oui, KawaiiFi::Security::CipherSuiteType::WEP40};
		}
	}

	unsigned int Wpa::pairwise_cipher_suite_count() const
	{
		if (bytes().size() < pairwise_cipher_suites_start) {
			return 0;
		}
		return bytes()[10] + (static_cast<std::uint8_t>(bytes()[11]) << 8U);
	}

	QVector<KawaiiFi::Security::CipherSuite> Wpa::pairwise_cipher_suites() const
	{
		QVector<KawaiiFi::Security::CipherSuite> cipher_suites;
		if (static_cast<unsigned int>(bytes().size()) <
		    (pairwise_cipher_suites_start + pairwise_cipher_suite_count() * 4)) {
			return cipher_suites;
		}
		auto it = bytes().begin() + pairwise_cipher_suites_start;
		const auto end_it = it + pairwise_cipher_suite_count() * 4;
		while (it < end_it) {
			std::array<std::uint8_t, 3> oui = {static_cast<std::uint8_t>(*it),
			                                   static_cast<std::uint8_t>(*(it + 1)),
			                                   static_cast<std::uint8_t>(*(it + 2))};
			switch (*(it + 3)) {
			case 0:
				cipher_suites.append({oui, KawaiiFi::Security::CipherSuiteType::SameAsGroupCipher});
				break;
			case 1:
				cipher_suites.append({oui, KawaiiFi::Security::CipherSuiteType::WEP40});
				break;
			case 2:
				cipher_suites.append({oui, KawaiiFi::Security::CipherSuiteType::TKIP});
				break;
			case 5:
				cipher_suites.append({oui, KawaiiFi::Security::CipherSuiteType::WEP104});
				break;
			}
			it += 4;
		}
		return cipher_suites;
	}

	unsigned int Wpa::akm_suite_count() const
	{
		if (bytes().size() < akm_suites_start()) {
			return 0;
		}
		return static_cast<std::uint8_t>(bytes()[8 + (pairwise_cipher_suite_count() * 4)]) +
		       (static_cast<std::uint8_t>(bytes()[8 + (pairwise_cipher_suite_count() * 4) + 1])
		        << 8U);
	}

	QVector<KawaiiFi::Security::AkmSuite> Wpa::akm_suites() const
	{
		QVector<KawaiiFi::Security::AkmSuite> akm_suites;
		if (bytes().size() < wpa_capabilities_start()) {
			return akm_suites;
		}
		auto it = bytes().begin() + akm_suites_start();
		const auto end_it = it + akm_suite_count() * 4;
		while (it < end_it) {
			std::array<unsigned char, 3> oui = {static_cast<unsigned char>(*it),
			                                    static_cast<unsigned char>(*(it + 1)),
			                                    static_cast<unsigned char>(*(it + 2))};
			switch (*(it + 3)) {
			case 1:
				akm_suites.append({oui, KawaiiFi::Security::AkmSuiteType::IEEE_8021X});
				break;
			case 2:
				akm_suites.append({oui, KawaiiFi::Security::AkmSuiteType::PSK});
			}
			it += 4;
		}
		return akm_suites;
	}

	QByteArray::size_type Wpa::akm_suites_start() const
	{
		return pairwise_cipher_suites_start +
		       static_cast<QByteArray::size_type>(pairwise_cipher_suite_count() * 4) + 2;
	}

	QByteArray::size_type Wpa::wpa_capabilities_start() const
	{
		return akm_suites_start() + static_cast<QByteArray::size_type>(akm_suite_count() * 4);
	}
} // namespace KawaiiFi::Ies
