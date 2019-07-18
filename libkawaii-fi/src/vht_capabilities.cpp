#include "libkawaii-fi/vht_capabilities.h"

#include <QDBusArgument>

namespace {
	const unsigned int vht_capability_ie_length = 12;
}

bool VhtCapabilities::supported() const { return supported_; }

unsigned int VhtCapabilities::max_mpdu_length() const { return max_mpdu_length_; }

VhtSupportedChannelWidth VhtCapabilities::supported_channel_width() const
{
	return supported_channel_width_;
}

bool VhtCapabilities::rx_ldpc() const { return rx_ldpc_; }

bool VhtCapabilities::short_gi_80_mhz() const { return short_gi_80_mhz_; }

bool VhtCapabilities::short_gi_160_mhz() const { return short_gi_160_mhz_; }

VhtTxStbc VhtCapabilities::tx_stbc() const { return tx_stbc_; }

VhtRxStbc VhtCapabilities::rx_stbc() const { return rx_stbc_; }

bool VhtCapabilities::su_beamformer_capable() const { return su_beamformer_capable_; }

bool VhtCapabilities::su_beamformee_capable() const { return su_beamformee_capable_; }

unsigned int VhtCapabilities::beamformee_sts() const { return beamformee_sts_; }

unsigned int VhtCapabilities::sounding_dimensions() const { return sounding_dimensions_; }

bool VhtCapabilities::mu_beamformer_capable() const { return mu_beamformer_capable_; }

bool VhtCapabilities::mu_beamformee_capable() const { return mu_beamformee_capable_; }

bool VhtCapabilities::vht_txop_ps() const { return vht_txop_ps_; }

bool VhtCapabilities::htc_vht_capable() const { return htc_vht_capable_; }

unsigned int VhtCapabilities::max_ampdu_length() const { return max_ampdu_length_; }

LinkAdaptation VhtCapabilities::link_adaptation() const { return link_adaptation_; }

bool VhtCapabilities::rx_antenna_pattern_consistent() const
{
	return rx_antenna_pattern_consistent_;
}

bool VhtCapabilities::tx_antenna_pattern_consistent() const
{
	return tx_antenna_pattern_consistent_;
}

VhtMcs VhtCapabilities::mcs_rx_one_ss() const { return mcs_rx_one_ss_; }

VhtMcs VhtCapabilities::mcs_rx_two_ss() const { return mcs_rx_two_ss_; }

VhtMcs VhtCapabilities::mcs_rx_three_ss() const { return mcs_rx_three_ss_; }

VhtMcs VhtCapabilities::mcs_rx_four_ss() const { return mcs_rx_four_ss_; }

VhtMcs VhtCapabilities::mcs_rx_five_ss() const { return mcs_rx_five_ss_; }

VhtMcs VhtCapabilities::mcs_rx_six_ss() const { return mcs_rx_six_ss_; }

VhtMcs VhtCapabilities::mcs_rx_seven_ss() const { return mcs_rx_seven_ss_; }

VhtMcs VhtCapabilities::mcs_rx_eight_ss() const { return mcs_rx_eight_ss_; }

unsigned int VhtCapabilities::rx_highest_long_gi_data_rate() const
{
	return rx_highest_long_gi_data_rate_;
}

unsigned int VhtCapabilities::max_nsts_total() const { return max_nsts_total_; }

VhtMcs VhtCapabilities::mcs_tx_one_ss() const { return mcs_tx_one_ss_; }

VhtMcs VhtCapabilities::mcs_tx_two_ss() const { return mcs_tx_two_ss_; }

VhtMcs VhtCapabilities::mcs_tx_three_ss() const { return mcs_tx_three_ss_; }

VhtMcs VhtCapabilities::mcs_tx_four_ss() const { return mcs_tx_four_ss_; }

VhtMcs VhtCapabilities::mcs_tx_five_ss() const { return mcs_tx_five_ss_; }

VhtMcs VhtCapabilities::mcs_tx_six_ss() const { return mcs_tx_six_ss_; }

VhtMcs VhtCapabilities::mcs_tx_seven_ss() const { return mcs_tx_seven_ss_; }

VhtMcs VhtCapabilities::mcs_tx_eight_ss() const { return mcs_tx_eight_ss_; }

unsigned int VhtCapabilities::tx_highest_long_gi_data_rate() const
{
	return tx_highest_long_gi_data_rate_;
}

bool VhtCapabilities::extended_nss_bw_capable() const { return extended_nss_bw_capable_; }

void VhtCapabilities::parse_ie(std::string_view ie_data)
{
	if (ie_data.size() != vht_capability_ie_length) {
		return;
	}

	supported_ = true;
}

QDBusArgument &operator<<(QDBusArgument &argument, const VhtCapabilities &vht_cap)
{
	argument.beginStructure();
	argument << vht_cap.supported_ << vht_cap.max_mpdu_length_
	         << static_cast<int>(vht_cap.supported_channel_width_) << vht_cap.rx_ldpc_
	         << vht_cap.short_gi_80_mhz_ << vht_cap.short_gi_160_mhz_
	         << static_cast<int>(vht_cap.tx_stbc_) << static_cast<int>(vht_cap.rx_stbc_)
	         << vht_cap.su_beamformer_capable_ << vht_cap.su_beamformee_capable_
	         << vht_cap.beamformee_sts_ << vht_cap.sounding_dimensions_
	         << vht_cap.mu_beamformer_capable_ << vht_cap.mu_beamformee_capable_
	         << vht_cap.vht_txop_ps_ << vht_cap.htc_vht_capable_ << vht_cap.max_ampdu_length_
	         << static_cast<int>(vht_cap.link_adaptation_) << vht_cap.rx_antenna_pattern_consistent_
	         << vht_cap.tx_antenna_pattern_consistent_ << static_cast<int>(vht_cap.mcs_rx_one_ss_)
	         << static_cast<int>(vht_cap.mcs_rx_two_ss_)
	         << static_cast<int>(vht_cap.mcs_rx_three_ss_)
	         << static_cast<int>(vht_cap.mcs_rx_four_ss_)
	         << static_cast<int>(vht_cap.mcs_rx_five_ss_)
	         << static_cast<int>(vht_cap.mcs_rx_six_ss_)
	         << static_cast<int>(vht_cap.mcs_rx_seven_ss_)
	         << static_cast<int>(vht_cap.mcs_rx_eight_ss_) << vht_cap.rx_highest_long_gi_data_rate_
	         << vht_cap.max_nsts_total_ << static_cast<int>(vht_cap.mcs_tx_one_ss_)
	         << static_cast<int>(vht_cap.mcs_tx_two_ss_)
	         << static_cast<int>(vht_cap.mcs_tx_three_ss_)
	         << static_cast<int>(vht_cap.mcs_tx_four_ss_)
	         << static_cast<int>(vht_cap.mcs_tx_five_ss_)
	         << static_cast<int>(vht_cap.mcs_tx_six_ss_)
	         << static_cast<int>(vht_cap.mcs_tx_seven_ss_)
	         << static_cast<int>(vht_cap.mcs_tx_eight_ss_) << vht_cap.tx_highest_long_gi_data_rate_
	         << vht_cap.extended_nss_bw_capable_;
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, VhtCapabilities &vht_cap)
{
	argument.beginStructure();
	vht_cap.supported_ = qdbus_cast<bool>(argument);
	vht_cap.max_mpdu_length_ = qdbus_cast<unsigned int>(argument);
	vht_cap.supported_channel_width_ =
	        static_cast<VhtSupportedChannelWidth>(qdbus_cast<int>(argument));
	vht_cap.rx_ldpc_ = qdbus_cast<bool>(argument);
	vht_cap.short_gi_80_mhz_ = qdbus_cast<bool>(argument);
	vht_cap.short_gi_160_mhz_ = qdbus_cast<bool>(argument);
	vht_cap.tx_stbc_ = static_cast<VhtTxStbc>(qdbus_cast<int>(argument));
	vht_cap.rx_stbc_ = static_cast<VhtRxStbc>(qdbus_cast<int>(argument));
	vht_cap.su_beamformer_capable_ = qdbus_cast<bool>(argument);
	vht_cap.su_beamformee_capable_ = qdbus_cast<bool>(argument);
	vht_cap.beamformee_sts_ = qdbus_cast<unsigned int>(argument);
	vht_cap.sounding_dimensions_ = qdbus_cast<unsigned int>(argument);
	vht_cap.mu_beamformer_capable_ = qdbus_cast<bool>(argument);
	vht_cap.mu_beamformee_capable_ = qdbus_cast<bool>(argument);
	vht_cap.vht_txop_ps_ = qdbus_cast<bool>(argument);
	vht_cap.htc_vht_capable_ = qdbus_cast<bool>(argument);
	vht_cap.max_ampdu_length_ = qdbus_cast<unsigned int>(argument);
	vht_cap.link_adaptation_ = static_cast<LinkAdaptation>(qdbus_cast<int>(argument));
	vht_cap.rx_antenna_pattern_consistent_ = qdbus_cast<bool>(argument);
	vht_cap.tx_antenna_pattern_consistent_ = qdbus_cast<bool>(argument);
	vht_cap.mcs_rx_one_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.mcs_rx_two_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.mcs_rx_three_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.mcs_rx_four_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.mcs_rx_five_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.mcs_rx_six_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.mcs_rx_seven_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.mcs_rx_eight_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.rx_highest_long_gi_data_rate_ = qdbus_cast<unsigned int>(argument);
	vht_cap.max_nsts_total_ = qdbus_cast<unsigned int>(argument);
	vht_cap.mcs_tx_one_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.mcs_tx_two_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.mcs_tx_three_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.mcs_tx_four_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.mcs_tx_five_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.mcs_tx_six_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.mcs_tx_seven_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.mcs_tx_eight_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_cap.tx_highest_long_gi_data_rate_ = qdbus_cast<unsigned int>(argument);
	vht_cap.extended_nss_bw_capable_ = qdbus_cast<bool>(argument);
	argument.endStructure();
	return argument;
}
