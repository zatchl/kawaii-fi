#ifndef VHT_CAPABILITIES_H
#define VHT_CAPABILITIES_H

#include <QDBusArgument>
#include <QMetaType>

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

struct VhtCapabilities {
	bool supported = false;
	unsigned int max_mpdu_length = 0;
	VhtSupportedChannelWidth supported_channel_width = VhtSupportedChannelWidth::OneSixtyMhz;
	bool rx_ldpc = false;
	bool short_gi_80_mhz = false;
	bool short_gi_160_mhz = false;
	VhtTxStbc tx_stbc = VhtTxStbc::Disabled;
	VhtRxStbc rx_stbc = VhtRxStbc::Disabled;
	bool su_beamformer_capable = false;
	bool su_beamformee_capable = false;
	unsigned int beamformee_sts = 1;
	unsigned int sounding_dimensions = 1;
	bool mu_beamformer_capable = false;
	bool mu_beamformee_capable = false;
	bool vht_txop_ps = false;
	bool htc_vht_capable = false;
	unsigned int max_ampdu_length = 0;
	LinkAdaptation link_adaptation = LinkAdaptation::NotSupported;
	bool rx_antenna_pattern_consistent = false;
	bool tx_antenna_pattern_consistent = false;
	VhtMcs mcs_rx_one_ss = VhtMcs::NotSupported;
	VhtMcs mcs_rx_two_ss = VhtMcs::NotSupported;
	VhtMcs mcs_rx_three_ss = VhtMcs::NotSupported;
	VhtMcs mcs_rx_four_ss = VhtMcs::NotSupported;
	VhtMcs mcs_rx_five_ss = VhtMcs::NotSupported;
	VhtMcs mcs_rx_six_ss = VhtMcs::NotSupported;
	VhtMcs mcs_rx_seven_ss = VhtMcs::NotSupported;
	VhtMcs mcs_rx_eight_ss = VhtMcs::NotSupported;
	unsigned int rx_highest_long_gi_data_rate = 0;
	unsigned int max_nsts_total = 0;
	VhtMcs mcs_tx_one_ss = VhtMcs::NotSupported;
	VhtMcs mcs_tx_two_ss = VhtMcs::NotSupported;
	VhtMcs mcs_tx_three_ss = VhtMcs::NotSupported;
	VhtMcs mcs_tx_four_ss = VhtMcs::NotSupported;
	VhtMcs mcs_tx_five_ss = VhtMcs::NotSupported;
	VhtMcs mcs_tx_six_ss = VhtMcs::NotSupported;
	VhtMcs mcs_tx_seven_ss = VhtMcs::NotSupported;
	VhtMcs mcs_tx_eight_ss = VhtMcs::NotSupported;
	unsigned int tx_highest_long_gi_data_rate = 0;
	bool extended_nss_bw_capable = false;
};
Q_DECLARE_METATYPE(VhtCapabilities)

// Marshall the VHT Capability data into a D-Bus argument
QDBusArgument &operator<<(QDBusArgument &argument, const VhtCapabilities &vht_cap);

// Retrieve the VHT Capability data from the D-Bus argument
const QDBusArgument &operator>>(const QDBusArgument &argument, VhtCapabilities &vht_cap);

#endif // VHT_CAPABILITIES_H
