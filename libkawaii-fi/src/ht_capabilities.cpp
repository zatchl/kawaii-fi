#include "libkawaii-fi/ht_capabilities.h"

QDBusArgument &operator<<(QDBusArgument &argument, const HtCapabilities &ht_cap)
{
	argument.beginStructure();
	argument << ht_cap.supported << ht_cap.ldpc_coding_capability
	         << static_cast<int>(ht_cap.supported_channel_width_set)
	         << static_cast<int>(ht_cap.sm_power_save) << ht_cap.greenfield_ppdu
	         << ht_cap.short_gi_20_mhz << ht_cap.short_gi_40_mhz << static_cast<int>(ht_cap.tx_stbc)
	         << static_cast<int>(ht_cap.rx_stbc) << ht_cap.delayed_block_ack
	         << ht_cap.max_amsdu_length << ht_cap.dsss_cck_40_mhz << ht_cap.psmp_support
	         << ht_cap.forty_mhz_intolerant << ht_cap.lsig_txop_protection
	         << ht_cap.max_ampdu_length << ht_cap.mpdu_density_usec << ht_cap.rx_mcs
	         << ht_cap.highest_supported_data_rate << ht_cap.tx_mcs_defined
	         << ht_cap.tx_rx_mcs_equal << ht_cap.max_tx_spatial_streams
	         << ht_cap.tx_unequal_modulation << ht_cap.pco_support << ht_cap.pco_transition_time
	         << ht_cap.mcs_feedback << ht_cap.htc_support << ht_cap.rd_responder;
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, HtCapabilities &ht_cap)
{
	int supported_channel_width = 0;
	int sm_power_save = 0;
	int tx_stbc = 0;
	int rx_stbc = 0;
	argument.beginStructure();
	argument >> ht_cap.supported >> ht_cap.ldpc_coding_capability >> supported_channel_width >>
	        sm_power_save >> ht_cap.greenfield_ppdu >> ht_cap.short_gi_20_mhz >>
	        ht_cap.short_gi_40_mhz >> tx_stbc >> rx_stbc >> ht_cap.delayed_block_ack >>
	        ht_cap.max_amsdu_length >> ht_cap.dsss_cck_40_mhz >> ht_cap.psmp_support >>
	        ht_cap.forty_mhz_intolerant >> ht_cap.lsig_txop_protection >> ht_cap.max_ampdu_length >>
	        ht_cap.mpdu_density_usec >> ht_cap.rx_mcs >> ht_cap.highest_supported_data_rate >>
	        ht_cap.tx_mcs_defined >> ht_cap.tx_rx_mcs_equal >> ht_cap.max_tx_spatial_streams >>
	        ht_cap.tx_unequal_modulation >> ht_cap.pco_support >> ht_cap.pco_transition_time >>
	        ht_cap.mcs_feedback >> ht_cap.htc_support >> ht_cap.rd_responder;
	argument.endStructure();
	ht_cap.supported_channel_width_set =
	        static_cast<HtSupportedChannelWidth>(supported_channel_width);
	ht_cap.sm_power_save = static_cast<SmPowerSave>(sm_power_save);
	ht_cap.tx_stbc = static_cast<HtTxStbc>(tx_stbc);
	ht_cap.rx_stbc = static_cast<HtRxStbc>(rx_stbc);
	return argument;
}
