#ifndef HT_CAPABILITIES_H
#define HT_CAPABILITIES_H

#include <QMetaType>
#include <QVector>
#include <cstdint>
#include <string_view>

class QDBusArgument;

enum class HtSupportedChannelWidth { TwentyMhz, TwentyOrFortyMhz };

enum class SmPowerSave { Static, Dynamic, Disabled };

enum class HtTxStbc { Disabled, Enabled };

enum class HtRxStbc { Disabled, OneSpatialStream, TwoSpatialStreams, ThreeSpatialStreams };

class HtCapabilities {
public:
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

	void parse_ie(std::string_view ie_data);

	// Marshall the HT Capability data into a D-Bus argument
	friend QDBusArgument &operator<<(QDBusArgument &argument, const HtCapabilities &ht_cap);

	// Retrieve the HT Capability data from the D-Bus argument
	friend const QDBusArgument &operator>>(const QDBusArgument &argument, HtCapabilities &ht_cap);

private:
	bool supported_ = false;
	// HT Capabilities Info
	bool ldpc_coding_capability_ = false;
	HtSupportedChannelWidth supported_channel_width_set_ = HtSupportedChannelWidth::TwentyMhz;
	SmPowerSave sm_power_save_ = SmPowerSave::Disabled;
	bool greenfield_ppdu_ = false;
	bool short_gi_20_mhz_ = false;
	bool short_gi_40_mhz_ = false;
	HtTxStbc tx_stbc_ = HtTxStbc::Disabled;
	HtRxStbc rx_stbc_ = HtRxStbc::Disabled;
	bool delayed_block_ack_ = false;
	unsigned int max_amsdu_length_ = 3839;
	bool dsss_cck_40_mhz_ = false;
	bool psmp_support_ = false;
	bool forty_mhz_intolerant_ = true;
	bool lsig_txop_protection_ = false;

	// A-MPDU
	unsigned int max_ampdu_length_ = 8191;
	unsigned int mpdu_density_usec_ = 0;

	// MCS
	QVector<std::uint8_t> rx_mcs_;
	unsigned int highest_supported_data_rate_ = 0;
	bool tx_mcs_defined_ = false;
	bool tx_rx_mcs_equal_ = true;
	unsigned int max_tx_spatial_streams_ = 0;
	bool tx_unequal_modulation_ = false;

	// HT Extended Capabilities
	bool pco_support_ = false;
	unsigned int pco_transition_time_ = 0;
	bool mcs_feedback_ = false;
	bool htc_support_ = false;
	bool rd_responder_ = false;
};
Q_DECLARE_METATYPE(HtCapabilities)

#endif // HT_CAPABILITIES_H
