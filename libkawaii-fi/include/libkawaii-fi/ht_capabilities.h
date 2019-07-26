#ifndef HT_CAPABILITIES_H
#define HT_CAPABILITIES_H

#include "information_element.h"

#include <QMetaType>
#include <QVector>
#include <cstdint>

enum class HtSupportedChannelWidth { TwentyMhz, TwentyOrFortyMhz };

enum class SmPowerSave { Static, Dynamic, Disabled };

enum class HtTxStbc { Disabled, Enabled };

enum class HtRxStbc { Disabled, OneSpatialStream, TwoSpatialStreams, ThreeSpatialStreams };

class HtCapabilities : public InformationElement {
public:
	HtCapabilities() = default;
	HtCapabilities(const InformationElement &ie);

	[[nodiscard]] bool supported() const;
	[[nodiscard]] bool ldpc_coding_capability() const;
	[[nodiscard]] HtSupportedChannelWidth supported_channel_width_set() const;
	[[nodiscard]] SmPowerSave sm_power_save() const;
	[[nodiscard]] bool greenfield_ppdu() const;
	[[nodiscard]] bool short_gi_20_mhz() const;
	[[nodiscard]] bool short_gi_40_mhz() const;
	[[nodiscard]] HtTxStbc tx_stbc() const;
	[[nodiscard]] HtRxStbc rx_stbc() const;
	[[nodiscard]] bool delayed_block_ack() const;
	[[nodiscard]] unsigned int max_amsdu_length() const;
	[[nodiscard]] bool dsss_cck_40_mhz() const;
	[[nodiscard]] bool psmp_support() const;
	[[nodiscard]] bool forty_mhz_intolerant() const;
	[[nodiscard]] bool lsig_txop_protection() const;

	[[nodiscard]] unsigned int max_ampdu_length() const;
	[[nodiscard]] unsigned int mpdu_density_usec() const;

	[[nodiscard]] QVector<std::uint8_t> rx_mcs() const;
	[[nodiscard]] unsigned int highest_supported_data_rate() const;
	[[nodiscard]] bool tx_mcs_defined() const;
	[[nodiscard]] bool tx_rx_mcs_equal() const;
	[[nodiscard]] unsigned int max_tx_spatial_streams() const;
	[[nodiscard]] bool tx_unequal_modulation() const;

	[[nodiscard]] bool pco_support() const;
	[[nodiscard]] unsigned int pco_transition_time() const;
	[[nodiscard]] bool mcs_feedback() const;
	[[nodiscard]] bool htc_support() const;
	[[nodiscard]] bool rd_responder() const;
};
Q_DECLARE_METATYPE(HtCapabilities)

inline const unsigned int WLAN_EID_HT_CAPABILITY = 45;

#endif // HT_CAPABILITIES_H
