#include "libkawaii-fi/ies/robust_security_network.h"

#include "libkawaii-fi/ies/information_element.h"
#include "libkawaii-fi/security.h"
#include "standard-items/rsn_standard_item.h"

#include <QByteArray>
#include <array>
#include <cstdint>

class QStandardItem;

namespace KawaiiFi::Ies {
	RobustSecurityNetwork::RobustSecurityNetwork(const std::string_view &bytes)
	    : InformationElement(bytes, WLAN_EID_RSN)
	{
	}

	QStandardItem *RobustSecurityNetwork::standard_item() const
	{
		return new RsnStandardItem(*this);
	}

	unsigned int RobustSecurityNetwork::version() const
	{
		if (bytes().size() < 2) {
			return 1;
		}
		return static_cast<std::uint8_t>(bytes()[0]) +
		       (static_cast<std::uint8_t>(bytes()[1]) << 8U);
	}

	Security::CipherSuite RobustSecurityNetwork::group_cipher_suite() const
	{
		if (bytes().size() < 6) {
			return Security::CipherSuite();
		}
		std::array<std::uint8_t, 3> oui = {static_cast<std::uint8_t>(bytes()[2]),
		                                   static_cast<std::uint8_t>(bytes()[3]),
		                                   static_cast<std::uint8_t>(bytes()[4])};
		switch (bytes()[5]) {
		case 1:
			return {oui, Security::CipherSuiteType::WEP40};
		case 2:
			return {oui, Security::CipherSuiteType::TKIP};
		case 4:
			return {oui, Security::CipherSuiteType::CCMP};
		case 5:
			return {oui, Security::CipherSuiteType::WEP104};
		default:
			return {oui, Security::CipherSuiteType::WEP40};
		}
	}

	unsigned int RobustSecurityNetwork::pairwise_cipher_suite_count() const
	{
		if (static_cast<unsigned int>(bytes().size()) < pairwise_cipher_suites_start()) {
			return 0;
		}
		return static_cast<std::uint8_t>(bytes()[6]) +
		       (static_cast<std::uint8_t>(bytes()[7]) << 8U);
	}

	QVector<Security::CipherSuite> RobustSecurityNetwork::pairwise_cipher_suites() const
	{
		QVector<Security::CipherSuite> cipher_suites;
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
				cipher_suites.append({oui, Security::CipherSuiteType::SameAsGroupCipher});
				break;
			case 1:
				cipher_suites.append({oui, Security::CipherSuiteType::WEP40});
				break;
			case 2:
				cipher_suites.append({oui, Security::CipherSuiteType::TKIP});
				break;
			case 4:
				cipher_suites.append({oui, Security::CipherSuiteType::CCMP});
				break;
			case 5:
				cipher_suites.append({oui, Security::CipherSuiteType::WEP104});
				break;
			}
			it += 4;
		}
		return cipher_suites;
	}

	unsigned int RobustSecurityNetwork::akm_suite_count() const
	{
		if (static_cast<unsigned int>(bytes().size()) < akm_suites_start()) {
			return 0;
		}
		return static_cast<std::uint8_t>(bytes()[8 + (pairwise_cipher_suite_count() * 4)]) +
		       (static_cast<std::uint8_t>(bytes()[8 + (pairwise_cipher_suite_count() * 4) + 1])
		        << 8U);
	}

	QVector<Security::AkmSuite> RobustSecurityNetwork::akm_suites() const
	{
		QVector<Security::AkmSuite> akm_suites;
		if (static_cast<unsigned int>(bytes().size()) < rsn_capabilities_start()) {
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
				akm_suites.append({oui, Security::AkmSuiteType::IEEE_8021X});
				break;
			case 2:
				akm_suites.append({oui, Security::AkmSuiteType::PSK});
			}
			it += 4;
		}
		return akm_suites;
	}

	bool RobustSecurityNetwork::pre_auth_capabilities() const { return false; }

	bool RobustSecurityNetwork::no_pairwise_capabilities() const { return false; }

	unsigned int RobustSecurityNetwork::ptksa_replay_counter_capabilities() const { return false; }

	unsigned int RobustSecurityNetwork::gtksa_replay_counter_capabilities() const { return false; }

	bool RobustSecurityNetwork::management_frame_protection_required() const { return false; }

	bool RobustSecurityNetwork::management_frame_protection_capable() const { return false; }

	bool RobustSecurityNetwork::joint_multi_band_rsna() const { return false; }

	bool RobustSecurityNetwork::peerkey_enabled() const { return false; }

	unsigned int RobustSecurityNetwork::pairwise_cipher_suites_start() const { return 8; }

	unsigned int RobustSecurityNetwork::akm_suites_start() const
	{
		return pairwise_cipher_suites_start() + (pairwise_cipher_suite_count() * 4) + 2;
	}

	unsigned int RobustSecurityNetwork::rsn_capabilities_start() const
	{
		return akm_suites_start() + (akm_suite_count() * 4);
	}
} // namespace KawaiiFi::Ies
