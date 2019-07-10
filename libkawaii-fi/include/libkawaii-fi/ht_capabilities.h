#ifndef HT_CAPABILITIES_H
#define HT_CAPABILITIES_H

#include <QDBusArgument>
#include <QMetaType>
#include <QVector>

enum class HtSupportedChannelWidth { TwentyMhz, TwentyOrFortyMhz };

enum class SmPowerSave { Static, Dynamic, Disabled };

enum class HtTxStbc { Disabled, Enabled };

enum class HtRxStbc { Disabled, OneSpatialStream, TwoSpatialStreams, ThreeSpatialStreams };

struct HtCapabilities {
	bool supported = false;
	// HT Capabilities Info
	bool ldpc_coding_capability = false;
	HtSupportedChannelWidth supported_channel_width_set = HtSupportedChannelWidth::TwentyMhz;
	SmPowerSave sm_power_save = SmPowerSave::Disabled;
	bool greenfield_ppdu = false;
	bool short_gi_20_mhz = false;
	bool short_gi_40_mhz = false;
	HtTxStbc tx_stbc = HtTxStbc::Disabled;
	HtRxStbc rx_stbc = HtRxStbc::Disabled;
	bool delayed_block_ack = false;
	unsigned int max_amsdu_length = 3839;
	bool dsss_cck_40_mhz = false;
	bool psmp_support = false;
	bool forty_mhz_intolerant = true;
	bool lsig_txop_protection = false;

	// A-MPDU
	unsigned int max_ampdu_length = 8191;
	unsigned int mpdu_density_usec = 0;

	// MCS
	QVector<uint8_t> rx_mcs;
	unsigned int highest_supported_data_rate = 0;
	bool tx_mcs_defined = false;
	bool tx_rx_mcs_equal = true;
	unsigned int max_tx_spatial_streams = 0;
	bool tx_unequal_modulation = false;

	// HT Extended Capabilities
	bool pco_support = false;
	unsigned int pco_transition_time = 0;
	bool mcs_feedback = false;
	bool htc_support = false;
	bool rd_responder = false;
};
Q_DECLARE_METATYPE(HtCapabilities)

// Marshall the HT Capability data into a D-Bus argument
QDBusArgument &operator<<(QDBusArgument &argument, const HtCapabilities &ht_cap);

// Retrieve the HT Capability data from the D-Bus argument
const QDBusArgument &operator>>(const QDBusArgument &argument, HtCapabilities &ht_cap);

#endif // HT_CAPABILITIES_H
