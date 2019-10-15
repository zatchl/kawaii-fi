#ifndef ROBUST_SECURITY_NETWORK_H
#define ROBUST_SECURITY_NETWORK_H

#include "information_element.h"
#include "libkawaii-fi/security.h"

#include <QVector>
#include <string_view>

class QStandardItem;

namespace KawaiiFi::Ies {
	class RobustSecurityNetwork : public InformationElement {
	public:
		RobustSecurityNetwork() = default;
		explicit RobustSecurityNetwork(const std::string_view &bytes);

		[[nodiscard]] QStandardItem *standard_item() const override;

		[[nodiscard]] unsigned int version() const;
		[[nodiscard]] KawaiiFi::Security::CipherSuite group_cipher_suite() const;
		[[nodiscard]] unsigned int pairwise_cipher_suite_count() const;
		[[nodiscard]] QVector<KawaiiFi::Security::CipherSuite> pairwise_cipher_suites() const;
		[[nodiscard]] unsigned int akm_suite_count() const;
		[[nodiscard]] QVector<KawaiiFi::Security::AkmSuite> akm_suites() const;

		[[nodiscard]] bool pre_auth_capabilities() const;
		[[nodiscard]] bool no_pairwise_capabilities() const;
		[[nodiscard]] unsigned int ptksa_replay_counter_capabilities() const;
		[[nodiscard]] unsigned int gtksa_replay_counter_capabilities() const;
		[[nodiscard]] bool management_frame_protection_required() const;
		[[nodiscard]] bool management_frame_protection_capable() const;
		[[nodiscard]] bool joint_multi_band_rsna() const;
		[[nodiscard]] bool peerkey_enabled() const;

	private:
		[[nodiscard]] unsigned int pairwise_cipher_suites_start() const;
		[[nodiscard]] unsigned int akm_suites_start() const;
		[[nodiscard]] unsigned int rsn_capabilities_start() const;
	};

	inline const unsigned int WLAN_EID_RSN = 48;
} // namespace KawaiiFi::Ies

#endif // ROBUST_SECURITY_NETWORK_H
