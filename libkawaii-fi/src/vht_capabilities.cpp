#include "libkawaii-fi/vht_capabilities.h"

#include "libkawaii-fi/information_element.h"

namespace {
	const unsigned int vht_capability_ie_length = 12;
}

VhtCapabilities::VhtCapabilities(const InformationElement &ie) : InformationElement(ie.bytes()) {}

bool VhtCapabilities::supported() const { return false; }

unsigned int VhtCapabilities::max_mpdu_length() const { return 0; }

VhtSupportedChannelWidth VhtCapabilities::supported_channel_width() const
{
	return VhtSupportedChannelWidth::NoOneSixtyMhzNoEightyPlusEightyMhz;
}

bool VhtCapabilities::rx_ldpc() const { return false; }

bool VhtCapabilities::short_gi_80_mhz() const { return false; }

bool VhtCapabilities::short_gi_160_mhz() const { return false; }

VhtTxStbc VhtCapabilities::tx_stbc() const { return VhtTxStbc::Disabled; }

VhtRxStbc VhtCapabilities::rx_stbc() const { return VhtRxStbc::Disabled; }

bool VhtCapabilities::su_beamformer_capable() const { return false; }

bool VhtCapabilities::su_beamformee_capable() const { return false; }

unsigned int VhtCapabilities::beamformee_sts() const { return 0; }

unsigned int VhtCapabilities::sounding_dimensions() const { return 0; }

bool VhtCapabilities::mu_beamformer_capable() const { return false; }

bool VhtCapabilities::mu_beamformee_capable() const { return false; }

bool VhtCapabilities::vht_txop_ps() const { return false; }

bool VhtCapabilities::htc_vht_capable() const { return false; }

unsigned int VhtCapabilities::max_ampdu_length() const { return 0; }

LinkAdaptation VhtCapabilities::link_adaptation() const { return LinkAdaptation::NotSupported; }

bool VhtCapabilities::rx_antenna_pattern_consistent() const { return false; }

bool VhtCapabilities::tx_antenna_pattern_consistent() const { return false; }

VhtMcs VhtCapabilities::mcs_rx_one_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtCapabilities::mcs_rx_two_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtCapabilities::mcs_rx_three_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtCapabilities::mcs_rx_four_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtCapabilities::mcs_rx_five_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtCapabilities::mcs_rx_six_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtCapabilities::mcs_rx_seven_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtCapabilities::mcs_rx_eight_ss() const { return VhtMcs::NotSupported; }

unsigned int VhtCapabilities::rx_highest_long_gi_data_rate() const { return 0; }

unsigned int VhtCapabilities::max_nsts_total() const { return 0; }

VhtMcs VhtCapabilities::mcs_tx_one_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtCapabilities::mcs_tx_two_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtCapabilities::mcs_tx_three_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtCapabilities::mcs_tx_four_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtCapabilities::mcs_tx_five_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtCapabilities::mcs_tx_six_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtCapabilities::mcs_tx_seven_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtCapabilities::mcs_tx_eight_ss() const { return VhtMcs::NotSupported; }

unsigned int VhtCapabilities::tx_highest_long_gi_data_rate() const { return 0; }

bool VhtCapabilities::extended_nss_bw_capable() const { return false; }
