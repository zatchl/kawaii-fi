#ifndef VHT_CAPABILITIES_H
#define VHT_CAPABILITIES_H

#include "information_element.h"

#include <array>
#include <string_view>

class QStandardItem;

namespace KawaiiFi::Ies {
	enum class VhtSupportedChannelWidth {
		NoOneSixtyMhzNoEightyPlusEightyMhz,
		OneSixtyMhz,
		OneSixtyMhzEightyPlusEightyMhz
	};

	enum class VhtRxStbc {
		NotSupported,
		OneSpatialStream,
		TwoSpatialStreams,
		ThreeSpatialStreams,
		FourSpatialStreams
	};

	enum class LinkAdaptation { NotSupported, SupportedUnsolicited, SupportedResponseUnsolicited };

	enum class VhtMcs { NotSupported, OneThroughSeven, OneThroughEight, OneThroughNine };

	class VhtCapabilities : public InformationElement {
	public:
		VhtCapabilities() = default;
		explicit VhtCapabilities(const std::string_view &bytes);

		[[nodiscard]] QStandardItem *standard_item() const override;

		[[nodiscard]] unsigned int max_mpdu_length() const;
		[[nodiscard]] VhtSupportedChannelWidth supported_channel_width_set() const;
		[[nodiscard]] bool rx_ldpc() const;
		[[nodiscard]] bool short_gi_80_mhz() const;
		[[nodiscard]] bool short_gi_160_mhz() const;
		[[nodiscard]] bool tx_stbc() const;
		[[nodiscard]] VhtRxStbc rx_stbc() const;
		[[nodiscard]] bool su_beamformer_capable() const;
		[[nodiscard]] bool su_beamformee_capable() const;
		[[nodiscard]] unsigned int beamformee_sts() const;
		[[nodiscard]] unsigned int sounding_dimensions() const;
		[[nodiscard]] bool mu_beamformer_capable() const;
		[[nodiscard]] bool mu_beamformee_capable() const;
		[[nodiscard]] bool vht_txop_ps() const;
		[[nodiscard]] bool htc_vht_capable() const;
		[[nodiscard]] unsigned int max_ampdu_length() const;
		[[nodiscard]] LinkAdaptation link_adaptation() const;
		[[nodiscard]] bool rx_antenna_pattern_consistent() const;
		[[nodiscard]] bool tx_antenna_pattern_consistent() const;
		[[nodiscard]] VhtMcs mcs_rx_one_ss() const;
		[[nodiscard]] VhtMcs mcs_rx_two_ss() const;
		[[nodiscard]] VhtMcs mcs_rx_three_ss() const;
		[[nodiscard]] VhtMcs mcs_rx_four_ss() const;
		[[nodiscard]] VhtMcs mcs_rx_five_ss() const;
		[[nodiscard]] VhtMcs mcs_rx_six_ss() const;
		[[nodiscard]] VhtMcs mcs_rx_seven_ss() const;
		[[nodiscard]] VhtMcs mcs_rx_eight_ss() const;
		[[nodiscard]] std::array<VhtMcs, 8> mcs_rx() const;
		[[nodiscard]] unsigned int rx_highest_long_gi_data_rate() const;
		[[nodiscard]] unsigned int max_nsts_total() const;
		[[nodiscard]] VhtMcs mcs_tx_one_ss() const;
		[[nodiscard]] VhtMcs mcs_tx_two_ss() const;
		[[nodiscard]] VhtMcs mcs_tx_three_ss() const;
		[[nodiscard]] VhtMcs mcs_tx_four_ss() const;
		[[nodiscard]] VhtMcs mcs_tx_five_ss() const;
		[[nodiscard]] VhtMcs mcs_tx_six_ss() const;
		[[nodiscard]] VhtMcs mcs_tx_seven_ss() const;
		[[nodiscard]] VhtMcs mcs_tx_eight_ss() const;
		[[nodiscard]] std::array<VhtMcs, 8> mcs_tx() const;
		[[nodiscard]] unsigned int tx_highest_long_gi_data_rate() const;
		[[nodiscard]] bool extended_nss_bw_capable() const;

	private:
		[[nodiscard]] VhtMcs bits_to_vht_mcs(int byte_index, unsigned int bit_index) const;
	};

	inline const unsigned int WLAN_EID_VHT_CAPABILITY = 191;
} // namespace KawaiiFi::Ies

#endif // VHT_CAPABILITIES_H
