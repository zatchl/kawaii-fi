#include "libkawaii-fi/ht_capabilities.h"

#include "libkawaii-fi/information_element.h"

namespace {
	const unsigned int ht_capability_ie_length = 26;
}

HtCapabilities::HtCapabilities(const InformationElement &ie) : InformationElement(ie.bytes()) {}

bool HtCapabilities::ldpc_coding_capability() const { return false; }

HtSupportedChannelWidth HtCapabilities::supported_channel_width_set() const
{
	return HtSupportedChannelWidth::TwentyMhz;
}

SmPowerSave HtCapabilities::sm_power_save() const { return SmPowerSave::Disabled; }

bool HtCapabilities::greenfield_ppdu() const { return false; }

bool HtCapabilities::short_gi_20_mhz() const { return false; }

bool HtCapabilities::short_gi_40_mhz() const { return false; }

HtTxStbc HtCapabilities::tx_stbc() const { return HtTxStbc::Disabled; }

HtRxStbc HtCapabilities::rx_stbc() const { return HtRxStbc::Disabled; }

bool HtCapabilities::delayed_block_ack() const { return false; }

unsigned int HtCapabilities::max_amsdu_length() const { return 0; }

bool HtCapabilities::dsss_cck_40_mhz() const { return false; }

bool HtCapabilities::psmp_support() const { return false; }

bool HtCapabilities::forty_mhz_intolerant() const { return false; }

bool HtCapabilities::lsig_txop_protection() const { return false; }

unsigned int HtCapabilities::max_ampdu_length() const { return 0; }

unsigned int HtCapabilities::mpdu_density_usec() const { return 0; }

QVector<uint8_t> HtCapabilities::rx_mcs() const { return QVector<uint8_t>(); }

unsigned int HtCapabilities::highest_supported_data_rate() const { return 0; }

bool HtCapabilities::tx_mcs_defined() const { return false; }

bool HtCapabilities::tx_rx_mcs_equal() const { return false; }

unsigned int HtCapabilities::max_tx_spatial_streams() const { return 0; }

bool HtCapabilities::tx_unequal_modulation() const { return false; }

bool HtCapabilities::pco_support() const { return false; }

unsigned int HtCapabilities::pco_transition_time() const { return 0; }

bool HtCapabilities::mcs_feedback() const { return false; }

bool HtCapabilities::htc_support() const { return false; }

bool HtCapabilities::rd_responder() const { return false; }
