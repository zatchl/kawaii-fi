#include "libkawaii-fi/ies/wpa.h"

#include "libkawaii-fi/ies/vendor_specific.h"

#include <QByteArray>
#include <cstdint>

Wpa::Wpa(const VendorSpecific &vs) : VendorSpecific(vs) {}

unsigned int Wpa::version() const
{
	if (bytes().size() < 6) {
		return 1;
	}
	return static_cast<std::uint8_t>(bytes()[4] + (bytes()[5] << 8));
}

CipherSuite Wpa::group_cipher_suite() const
{
	if (bytes().size() < 10) {
		return CipherSuite();
	}
	std::array<std::uint8_t, 3> oui = {static_cast<std::uint8_t>(bytes()[6]),
	                                   static_cast<std::uint8_t>(bytes()[7]),
	                                   static_cast<std::uint8_t>(bytes()[8])};
	switch (bytes()[9]) {
	case 1:
		return {oui, CipherSuiteType::WEP40};
	case 2:
		return {oui, CipherSuiteType::TKIP};
	case 5:
		return {oui, CipherSuiteType::WEP104};
	default:
		return {oui, CipherSuiteType::WEP40};
	}
}

unsigned int Wpa::pairwise_cipher_suite_count() const
{
	if (static_cast<unsigned int>(bytes().size()) < pairwise_cipher_suites_start()) {
		return 0;
	}
	return static_cast<unsigned int>(bytes()[10] + (bytes()[11] << 8));
}

QVector<CipherSuite> Wpa::pairwise_cipher_suites() const
{
	QVector<CipherSuite> cipher_suites;
	if (static_cast<unsigned int>(bytes().size()) <
	    (pairwise_cipher_suites_start() + pairwise_cipher_suite_count() * 4)) {
		return cipher_suites;
	}
	auto it = bytes().begin() + pairwise_cipher_suites_start();
	const auto end_it = it + pairwise_cipher_suite_count() * 4;
	while (it < end_it) {
		std::array<std::uint8_t, 3> oui = {static_cast<std::uint8_t>(*it),
		                                   static_cast<std::uint8_t>(*(it + 1)),
		                                   static_cast<std::uint8_t>(*(it + 2))};
		switch (*(it + 3)) {
		case 0:
			cipher_suites.append({oui, CipherSuiteType::SameAsGroupCipher});
			break;
		case 1:
			cipher_suites.append({oui, CipherSuiteType::WEP40});
			break;
		case 2:
			cipher_suites.append({oui, CipherSuiteType::TKIP});
			break;
		case 5:
			cipher_suites.append({oui, CipherSuiteType::WEP104});
			break;
		}
		it += 4;
	}
	return cipher_suites;
}

unsigned int Wpa::akm_suite_count() const
{
	if (static_cast<unsigned int>(bytes().size()) < akm_suites_start()) {
		return 0;
	}
	return static_cast<unsigned int>(bytes()[8 + (pairwise_cipher_suite_count() * 4)] +
	                                 (bytes()[8 + (pairwise_cipher_suite_count() * 4) + 1] << 8));
}

QVector<AkmSuite> Wpa::akm_suites() const
{
	QVector<AkmSuite> akm_suites;
	if (static_cast<unsigned int>(bytes().size()) < wpa_capabilities_start()) {
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
			akm_suites.append({oui, AkmSuiteType::IEEE_8021X});
			break;
		case 2:
			akm_suites.append({oui, AkmSuiteType::PSK});
		}
		it += 4;
	}
	return akm_suites;
}

unsigned int Wpa::pairwise_cipher_suites_start() const { return 12; }

unsigned int Wpa::akm_suites_start() const
{
	return pairwise_cipher_suites_start() + (pairwise_cipher_suite_count() * 4) + 2;
}

unsigned int Wpa::wpa_capabilities_start() const
{
	return akm_suites_start() + (akm_suite_count() * 4);
}
