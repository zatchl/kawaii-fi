#ifndef VHT_CAPABILITIES_H
#define VHT_CAPABILITIES_H

#include <QMetaType>
#include <string_view>

class QDBusArgument;

enum class VhtSupportedChannelWidth {
	NoOneSixtyMhzNoEightyPlusEightyMhz,
	OneSixtyMhz,
	OneSixtyMhzEightyPlusEightyMhz
};

enum class VhtTxStbc { Disabled, Enabled };

enum class VhtRxStbc {
	Disabled,
	OneSpatialStream,
	TwoSpatialStreams,
	ThreeSpatialStreams,
	FourSpatialStreams
};

enum class LinkAdaptation { NotSupported, SupportedUnsolicited, SupportedResponseUnsolicited };

enum class VhtMcs { NotSupported, OneThroughSeven, OneThroughEight, OneThroughNine };

class VhtCapabilities {
public:
	[[nodiscard]] bool supported() const;
	[[nodiscard]] unsigned int max_mpdu_length() const;
	[[nodiscard]] VhtSupportedChannelWidth supported_channel_width() const;
	[[nodiscard]] bool rx_ldpc() const;
	[[nodiscard]] bool short_gi_80_mhz() const;
	[[nodiscard]] bool short_gi_160_mhz() const;
	[[nodiscard]] VhtTxStbc tx_stbc() const;
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
	[[nodiscard]] unsigned int tx_highest_long_gi_data_rate() const;
	[[nodiscard]] bool extended_nss_bw_capable() const;

	void parse_ie(std::string_view ie_data);

	// Marshall the VHT Capability data into a D-Bus argument
	friend QDBusArgument &operator<<(QDBusArgument &argument, const VhtCapabilities &vht_cap);

	// Retrieve the VHT Capability data from the D-Bus argument
	friend const QDBusArgument &operator>>(const QDBusArgument &argument, VhtCapabilities &vht_cap);

private:
	bool supported_ = false;
	unsigned int max_mpdu_length_ = 0;
	VhtSupportedChannelWidth supported_channel_width_ = VhtSupportedChannelWidth::OneSixtyMhz;
	bool rx_ldpc_ = false;
	bool short_gi_80_mhz_ = false;
	bool short_gi_160_mhz_ = false;
	VhtTxStbc tx_stbc_ = VhtTxStbc::Disabled;
	VhtRxStbc rx_stbc_ = VhtRxStbc::Disabled;
	bool su_beamformer_capable_ = false;
	bool su_beamformee_capable_ = false;
	unsigned int beamformee_sts_ = 1;
	unsigned int sounding_dimensions_ = 1;
	bool mu_beamformer_capable_ = false;
	bool mu_beamformee_capable_ = false;
	bool vht_txop_ps_ = false;
	bool htc_vht_capable_ = false;
	unsigned int max_ampdu_length_ = 0;
	LinkAdaptation link_adaptation_ = LinkAdaptation::NotSupported;
	bool rx_antenna_pattern_consistent_ = false;
	bool tx_antenna_pattern_consistent_ = false;
	VhtMcs mcs_rx_one_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_rx_two_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_rx_three_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_rx_four_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_rx_five_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_rx_six_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_rx_seven_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_rx_eight_ss_ = VhtMcs::NotSupported;
	unsigned int rx_highest_long_gi_data_rate_ = 0;
	unsigned int max_nsts_total_ = 0;
	VhtMcs mcs_tx_one_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_tx_two_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_tx_three_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_tx_four_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_tx_five_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_tx_six_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_tx_seven_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_tx_eight_ss_ = VhtMcs::NotSupported;
	unsigned int tx_highest_long_gi_data_rate_ = 0;
	bool extended_nss_bw_capable_ = false;
};
Q_DECLARE_METATYPE(VhtCapabilities)

#endif // VHT_CAPABILITIES_H
