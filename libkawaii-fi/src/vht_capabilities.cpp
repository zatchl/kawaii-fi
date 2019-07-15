#include "libkawaii-fi/vht_capabilities.h"

QDBusArgument &operator<<(QDBusArgument &argument, const VhtCapabilities &vht_cap)
{
	argument.beginStructure();
	argument << vht_cap.supported << vht_cap.max_mpdu_length
	         << static_cast<int>(vht_cap.supported_channel_width) << vht_cap.rx_ldpc
	         << vht_cap.short_gi_80_mhz << vht_cap.short_gi_160_mhz
	         << static_cast<int>(vht_cap.tx_stbc) << static_cast<int>(vht_cap.rx_stbc)
	         << vht_cap.su_beamformer_capable << vht_cap.su_beamformee_capable
	         << vht_cap.beamformee_sts << vht_cap.sounding_dimensions
	         << vht_cap.mu_beamformer_capable << vht_cap.mu_beamformee_capable
	         << vht_cap.vht_txop_ps << vht_cap.htc_vht_capable << vht_cap.max_ampdu_length
	         << static_cast<int>(vht_cap.link_adaptation) << vht_cap.rx_antenna_pattern_consistent
	         << vht_cap.tx_antenna_pattern_consistent << static_cast<int>(vht_cap.mcs_rx_one_ss)
	         << static_cast<int>(vht_cap.mcs_rx_two_ss) << static_cast<int>(vht_cap.mcs_rx_three_ss)
	         << static_cast<int>(vht_cap.mcs_rx_four_ss) << static_cast<int>(vht_cap.mcs_rx_five_ss)
	         << static_cast<int>(vht_cap.mcs_rx_six_ss) << static_cast<int>(vht_cap.mcs_rx_seven_ss)
	         << static_cast<int>(vht_cap.mcs_rx_eight_ss) << vht_cap.rx_highest_long_gi_data_rate
	         << vht_cap.max_nsts_total << static_cast<int>(vht_cap.mcs_tx_one_ss)
	         << static_cast<int>(vht_cap.mcs_tx_two_ss) << static_cast<int>(vht_cap.mcs_tx_three_ss)
	         << static_cast<int>(vht_cap.mcs_tx_four_ss) << static_cast<int>(vht_cap.mcs_tx_five_ss)
	         << static_cast<int>(vht_cap.mcs_tx_six_ss) << static_cast<int>(vht_cap.mcs_tx_seven_ss)
	         << static_cast<int>(vht_cap.mcs_tx_eight_ss) << vht_cap.tx_highest_long_gi_data_rate
	         << vht_cap.extended_nss_bw_capable;
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, VhtCapabilities &vht_cap)
{
	int supported_channel_width = 0;
	int tx_stbc = 0;
	int rx_stbc = 0;
	int link_adaptation = 0;
	int mcs_rx_one_ss = 0;
	int mcs_rx_two_ss = 0;
	int mcs_rx_three_ss = 0;
	int mcs_rx_four_ss = 0;
	int mcs_rx_five_ss = 0;
	int mcs_rx_six_ss = 0;
	int mcs_rx_seven_ss = 0;
	int mcs_rx_eight_ss = 0;
	int mcs_tx_one_ss = 0;
	int mcs_tx_two_ss = 0;
	int mcs_tx_three_ss = 0;
	int mcs_tx_four_ss = 0;
	int mcs_tx_five_ss = 0;
	int mcs_tx_six_ss = 0;
	int mcs_tx_seven_ss = 0;
	int mcs_tx_eight_ss = 0;
	argument.beginStructure();
	argument >> vht_cap.supported >> vht_cap.max_mpdu_length >> supported_channel_width >>
	        vht_cap.rx_ldpc >> vht_cap.short_gi_80_mhz >> vht_cap.short_gi_160_mhz >> tx_stbc >>
	        rx_stbc >> vht_cap.su_beamformer_capable >> vht_cap.su_beamformee_capable >>
	        vht_cap.beamformee_sts >> vht_cap.sounding_dimensions >>
	        vht_cap.mu_beamformer_capable >> vht_cap.mu_beamformee_capable >> vht_cap.vht_txop_ps >>
	        vht_cap.htc_vht_capable >> vht_cap.max_ampdu_length >> link_adaptation >>
	        vht_cap.rx_antenna_pattern_consistent >> vht_cap.tx_antenna_pattern_consistent >>
	        mcs_rx_one_ss >> mcs_rx_two_ss >> mcs_rx_three_ss >> mcs_rx_four_ss >> mcs_rx_five_ss >>
	        mcs_rx_six_ss >> mcs_rx_seven_ss >> mcs_rx_eight_ss >>
	        vht_cap.rx_highest_long_gi_data_rate >> vht_cap.max_nsts_total >> mcs_tx_one_ss >>
	        mcs_tx_two_ss >> mcs_tx_three_ss >> mcs_tx_four_ss >> mcs_tx_five_ss >> mcs_tx_six_ss >>
	        mcs_tx_seven_ss >> mcs_tx_eight_ss >> vht_cap.tx_highest_long_gi_data_rate >>
	        vht_cap.extended_nss_bw_capable;
	argument.endStructure();
	vht_cap.supported_channel_width =
	        static_cast<VhtSupportedChannelWidth>(supported_channel_width);
	vht_cap.tx_stbc = static_cast<VhtTxStbc>(tx_stbc);
	vht_cap.rx_stbc = static_cast<VhtRxStbc>(rx_stbc);
	vht_cap.link_adaptation = static_cast<LinkAdaptation>(link_adaptation);
	vht_cap.mcs_rx_one_ss = static_cast<VhtMcs>(mcs_rx_one_ss);
	vht_cap.mcs_rx_two_ss = static_cast<VhtMcs>(mcs_rx_two_ss);
	vht_cap.mcs_rx_three_ss = static_cast<VhtMcs>(mcs_rx_three_ss);
	vht_cap.mcs_rx_four_ss = static_cast<VhtMcs>(mcs_rx_four_ss);
	vht_cap.mcs_rx_five_ss = static_cast<VhtMcs>(mcs_rx_five_ss);
	vht_cap.mcs_rx_six_ss = static_cast<VhtMcs>(mcs_rx_six_ss);
	vht_cap.mcs_rx_seven_ss = static_cast<VhtMcs>(mcs_rx_seven_ss);
	vht_cap.mcs_rx_eight_ss = static_cast<VhtMcs>(mcs_rx_eight_ss);
	vht_cap.mcs_tx_one_ss = static_cast<VhtMcs>(mcs_tx_one_ss);
	vht_cap.mcs_tx_two_ss = static_cast<VhtMcs>(mcs_tx_two_ss);
	vht_cap.mcs_tx_three_ss = static_cast<VhtMcs>(mcs_tx_three_ss);
	vht_cap.mcs_tx_four_ss = static_cast<VhtMcs>(mcs_tx_four_ss);
	vht_cap.mcs_tx_five_ss = static_cast<VhtMcs>(mcs_tx_five_ss);
	vht_cap.mcs_tx_six_ss = static_cast<VhtMcs>(mcs_tx_six_ss);
	vht_cap.mcs_tx_seven_ss = static_cast<VhtMcs>(mcs_tx_seven_ss);
	vht_cap.mcs_tx_eight_ss = static_cast<VhtMcs>(mcs_tx_eight_ss);
	return argument;
}
