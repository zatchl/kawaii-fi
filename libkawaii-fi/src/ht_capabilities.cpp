#include "libkawaii-fi/ht_capabilities.h"

#include <QDBusArgument>
#include <string_view>

namespace {
	const unsigned int ht_capability_ie_length = 26;
}

bool HtCapabilities::supported() const { return supported_; }

bool HtCapabilities::ldpc_coding_capability() const { return ldpc_coding_capability_; }

HtSupportedChannelWidth HtCapabilities::supported_channel_width_set() const
{
	return supported_channel_width_set_;
}

SmPowerSave HtCapabilities::sm_power_save() const { return sm_power_save_; }

bool HtCapabilities::greenfield_ppdu() const { return greenfield_ppdu_; }

bool HtCapabilities::short_gi_20_mhz() const { return short_gi_20_mhz_; }

bool HtCapabilities::short_gi_40_mhz() const { return short_gi_40_mhz_; }

HtTxStbc HtCapabilities::tx_stbc() const { return tx_stbc_; }

HtRxStbc HtCapabilities::rx_stbc() const { return rx_stbc_; }

bool HtCapabilities::delayed_block_ack() const { return delayed_block_ack_; }

unsigned int HtCapabilities::max_amsdu_length() const { return max_amsdu_length_; }

bool HtCapabilities::dsss_cck_40_mhz() const { return dsss_cck_40_mhz_; }

bool HtCapabilities::psmp_support() const { return psmp_support_; }

bool HtCapabilities::forty_mhz_intolerant() const { return forty_mhz_intolerant_; }

bool HtCapabilities::lsig_txop_protection() const { return lsig_txop_protection_; }

unsigned int HtCapabilities::max_ampdu_length() const { return max_ampdu_length_; }

unsigned int HtCapabilities::mpdu_density_usec() const { return mpdu_density_usec_; }

QVector<uint8_t> HtCapabilities::rx_mcs() const { return rx_mcs_; }

unsigned int HtCapabilities::highest_supported_data_rate() const
{
	return highest_supported_data_rate_;
}

bool HtCapabilities::tx_mcs_defined() const { return tx_mcs_defined_; }

bool HtCapabilities::tx_rx_mcs_equal() const { return tx_rx_mcs_equal_; }

unsigned int HtCapabilities::max_tx_spatial_streams() const { return max_tx_spatial_streams_; }

bool HtCapabilities::tx_unequal_modulation() const { return tx_unequal_modulation_; }

bool HtCapabilities::pco_support() const { return pco_support_; }

unsigned int HtCapabilities::pco_transition_time() const { return pco_transition_time_; }

bool HtCapabilities::mcs_feedback() const { return mcs_feedback_; }

bool HtCapabilities::htc_support() const { return htc_support_; }

bool HtCapabilities::rd_responder() const { return rd_responder_; }

void HtCapabilities::parse_ie(std::string_view ie_data)
{
	if (ie_data.size() != ht_capability_ie_length) {
		return;
	}

	supported_ = true;
}

QDBusArgument &operator<<(QDBusArgument &argument, const HtCapabilities &ht_cap)
{
	argument.beginStructure();
	argument << ht_cap.supported_ << ht_cap.ldpc_coding_capability_
	         << static_cast<int>(ht_cap.supported_channel_width_set_)
	         << static_cast<int>(ht_cap.sm_power_save_) << ht_cap.greenfield_ppdu_
	         << ht_cap.short_gi_20_mhz_ << ht_cap.short_gi_40_mhz_
	         << static_cast<int>(ht_cap.tx_stbc_) << static_cast<int>(ht_cap.rx_stbc_)
	         << ht_cap.delayed_block_ack_ << ht_cap.max_amsdu_length_ << ht_cap.dsss_cck_40_mhz_
	         << ht_cap.psmp_support_ << ht_cap.forty_mhz_intolerant_ << ht_cap.lsig_txop_protection_
	         << ht_cap.max_ampdu_length_ << ht_cap.mpdu_density_usec_ << ht_cap.rx_mcs_
	         << ht_cap.highest_supported_data_rate_ << ht_cap.tx_mcs_defined_
	         << ht_cap.tx_rx_mcs_equal_ << ht_cap.max_tx_spatial_streams_
	         << ht_cap.tx_unequal_modulation_ << ht_cap.pco_support_ << ht_cap.pco_transition_time_
	         << ht_cap.mcs_feedback_ << ht_cap.htc_support_ << ht_cap.rd_responder_;
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, HtCapabilities &ht_cap)
{
	argument.beginStructure();
	ht_cap.supported_ = qdbus_cast<bool>(argument);
	ht_cap.ldpc_coding_capability_ = qdbus_cast<bool>(argument);
	ht_cap.supported_channel_width_set_ =
	        static_cast<HtSupportedChannelWidth>(qdbus_cast<int>(argument));
	ht_cap.sm_power_save_ = static_cast<SmPowerSave>(qdbus_cast<int>(argument));
	ht_cap.greenfield_ppdu_ = qdbus_cast<bool>(argument);
	ht_cap.short_gi_20_mhz_ = qdbus_cast<bool>(argument);
	ht_cap.short_gi_40_mhz_ = qdbus_cast<bool>(argument);
	ht_cap.tx_stbc_ = static_cast<HtTxStbc>(qdbus_cast<int>(argument));
	ht_cap.rx_stbc_ = static_cast<HtRxStbc>(qdbus_cast<int>(argument));
	ht_cap.delayed_block_ack_ = qdbus_cast<bool>(argument);
	ht_cap.max_amsdu_length_ = qdbus_cast<unsigned int>(argument);
	ht_cap.dsss_cck_40_mhz_ = qdbus_cast<bool>(argument);
	ht_cap.psmp_support_ = qdbus_cast<bool>(argument);
	ht_cap.forty_mhz_intolerant_ = qdbus_cast<bool>(argument);
	ht_cap.lsig_txop_protection_ = qdbus_cast<bool>(argument);
	ht_cap.max_ampdu_length_ = qdbus_cast<unsigned int>(argument);
	ht_cap.mpdu_density_usec_ = qdbus_cast<unsigned int>(argument);
	ht_cap.rx_mcs_ = qdbus_cast<QVector<std::uint8_t>>(argument);
	ht_cap.highest_supported_data_rate_ = qdbus_cast<unsigned int>(argument);
	ht_cap.tx_mcs_defined_ = qdbus_cast<bool>(argument);
	ht_cap.tx_rx_mcs_equal_ = qdbus_cast<bool>(argument);
	ht_cap.max_tx_spatial_streams_ = qdbus_cast<unsigned int>(argument);
	ht_cap.tx_unequal_modulation_ = qdbus_cast<bool>(argument);
	ht_cap.pco_support_ = qdbus_cast<bool>(argument);
	ht_cap.pco_transition_time_ = qdbus_cast<unsigned int>(argument);
	ht_cap.mcs_feedback_ = qdbus_cast<bool>(argument);
	ht_cap.htc_support_ = qdbus_cast<bool>(argument);
	ht_cap.rd_responder_ = qdbus_cast<bool>(argument);
	argument.endStructure();
	return argument;
}
