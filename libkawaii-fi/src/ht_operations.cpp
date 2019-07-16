#include "libkawaii-fi/ht_operations.h"

#include "libkawaii-fi/ht_capabilities.h"

bool HtOperations::supported() const { return supported_; }

unsigned int HtOperations::primary_channel() const { return primary_channel_; }

SecondaryChannelOffset HtOperations::secondary_channel_offset() const
{
	return secondary_channel_offset_;
}

HtSupportedChannelWidth HtOperations::supported_channel_width() const
{
	return supported_channel_width_;
}

bool HtOperations::rifs() const { return rifs_; }

HtProtection HtOperations::ht_protection() const { return ht_protection_; }

bool HtOperations::non_greenfield_stas_present() const { return non_greenfield_stas_present_; }

bool HtOperations::obss_non_ht_stas_present() const { return obss_non_ht_stas_present_; }

unsigned int HtOperations::center_freq_segment_two() const { return center_freq_segment_two_; }

bool HtOperations::dual_beacon() const { return dual_beacon_; }

bool HtOperations::dual_cts_protection() const { return dual_cts_protection_; }

bool HtOperations::stbc_beacon() const { return stbc_beacon_; }

bool HtOperations::lsig_txop_protection_full_support() const
{
	return lsig_txop_protection_full_support_;
}

bool HtOperations::pco_active() const { return pco_active_; }

PcoPhase HtOperations::pco_phase() const { return pco_phase_; }

const QVector<std::uint8_t> &HtOperations::rx_mcs() const { return rx_mcs_; }

QVector<std::uint8_t> &HtOperations::rx_mcs() { return rx_mcs_; }

unsigned int HtOperations::highest_supported_data_rate() const
{
	return highest_supported_data_rate_;
}

bool HtOperations::tx_mcs_defined() const { return tx_mcs_defined_; }

bool HtOperations::tx_rx_mcs_equal() const { return tx_rx_mcs_equal_; }

unsigned int HtOperations::max_tx_spatial_streams() const { return max_tx_spatial_streams_; }

bool HtOperations::tx_unequal_modulation() const { return tx_unequal_modulation_; }

void HtOperations::set_supported(bool supported) { supported_ = supported; }

void HtOperations::set_primary_channel(unsigned int primary_channel)
{
	primary_channel_ = primary_channel;
}

void HtOperations::set_secondary_channel_offset(SecondaryChannelOffset secondary_channel_offset)
{
	secondary_channel_offset_ = secondary_channel_offset;
}

void HtOperations::set_supported_channel_width(HtSupportedChannelWidth supported_channel_width)
{
	supported_channel_width_ = supported_channel_width;
}

void HtOperations::set_rifs(bool rifs) { rifs_ = rifs; }

void HtOperations::set_ht_protection(HtProtection ht_protection) { ht_protection_ = ht_protection; }

void HtOperations::set_non_greenfield_stas_present(bool non_greenfield_stas_present)
{
	non_greenfield_stas_present_ = non_greenfield_stas_present;
}

void HtOperations::set_obss_non_ht_stas_present(bool obss_non_ht_stas_present)
{
	obss_non_ht_stas_present_ = obss_non_ht_stas_present;
}

void HtOperations::set_center_freq_segment_two(unsigned int center_freq_segment_two)
{
	center_freq_segment_two_ = center_freq_segment_two;
}

void HtOperations::set_dual_beacon(bool dual_beacon) { dual_beacon_ = dual_beacon; }

void HtOperations::set_dual_cts_protection(bool dual_cts_protection)
{
	dual_cts_protection_ = dual_cts_protection;
}

void HtOperations::set_stbc_beacon(bool stbc_beacon) { stbc_beacon_ = stbc_beacon; }

void HtOperations::set_lsig_txop_protection_full_support(bool lsig_txop_protection_full_support)
{
	lsig_txop_protection_full_support_ = lsig_txop_protection_full_support;
}

void HtOperations::set_pco_active(bool pco_active) { pco_active_ = pco_active; }

void HtOperations::set_pco_phase(PcoPhase pco_phase) { pco_phase_ = pco_phase; }

void HtOperations::set_rx_mcs(const QVector<uint8_t> &rx_mcs) { rx_mcs_ = rx_mcs; }

void HtOperations::set_highest_supported_data_rate(unsigned int highest_supported_data_rate)
{
	highest_supported_data_rate_ = highest_supported_data_rate;
}

void HtOperations::set_tx_mcs_defined(bool tx_mcs_defined) { tx_mcs_defined_ = tx_mcs_defined; }

void HtOperations::set_tx_rx_mcs_equal(bool tx_rx_mcs_equal) { tx_rx_mcs_equal_ = tx_rx_mcs_equal; }

void HtOperations::set_max_tx_spatial_streams(unsigned int max_tx_spatial_streams)
{
	max_tx_spatial_streams_ = max_tx_spatial_streams;
}

void HtOperations::set_tx_unequal_modulation(bool tx_unequal_modulation)
{
	tx_unequal_modulation_ = tx_unequal_modulation;
}

QDBusArgument &operator<<(QDBusArgument &argument, const HtOperations &ht_op)
{
	argument.beginStructure();
	argument << ht_op.supported() << ht_op.primary_channel()
	         << static_cast<int>(ht_op.secondary_channel_offset())
	         << static_cast<int>(ht_op.supported_channel_width()) << ht_op.rifs()
	         << static_cast<int>(ht_op.ht_protection()) << ht_op.non_greenfield_stas_present()
	         << ht_op.obss_non_ht_stas_present() << ht_op.center_freq_segment_two()
	         << ht_op.dual_beacon() << ht_op.dual_cts_protection() << ht_op.stbc_beacon()
	         << ht_op.lsig_txop_protection_full_support() << ht_op.pco_active()
	         << static_cast<int>(ht_op.pco_phase()) << ht_op.rx_mcs()
	         << ht_op.highest_supported_data_rate() << ht_op.tx_mcs_defined()
	         << ht_op.tx_rx_mcs_equal() << ht_op.max_tx_spatial_streams()
	         << ht_op.tx_unequal_modulation();
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, HtOperations &ht_op)
{
	argument.beginStructure();
	ht_op.set_supported(qdbus_cast<bool>(argument));
	ht_op.set_primary_channel(qdbus_cast<unsigned int>(argument));
	ht_op.set_secondary_channel_offset(
	        static_cast<SecondaryChannelOffset>(qdbus_cast<int>(argument)));
	ht_op.set_supported_channel_width(
	        static_cast<HtSupportedChannelWidth>(qdbus_cast<int>(argument)));
	ht_op.set_rifs(qdbus_cast<bool>(argument));
	ht_op.set_ht_protection(static_cast<HtProtection>(qdbus_cast<int>(argument)));
	ht_op.set_non_greenfield_stas_present(qdbus_cast<bool>(argument));
	ht_op.set_obss_non_ht_stas_present(qdbus_cast<bool>(argument));
	ht_op.set_center_freq_segment_two(qdbus_cast<unsigned int>(argument));
	ht_op.set_dual_beacon(qdbus_cast<bool>(argument));
	ht_op.set_dual_cts_protection(qdbus_cast<bool>(argument));
	ht_op.set_stbc_beacon(qdbus_cast<bool>(argument));
	ht_op.set_lsig_txop_protection_full_support(qdbus_cast<bool>(argument));
	ht_op.set_pco_active(qdbus_cast<bool>(argument));
	ht_op.set_pco_phase(static_cast<PcoPhase>(qdbus_cast<int>(argument)));
	ht_op.set_rx_mcs(qdbus_cast<QVector<std::uint8_t>>(argument));
	ht_op.set_highest_supported_data_rate(qdbus_cast<unsigned int>(argument));
	ht_op.set_tx_mcs_defined(qdbus_cast<bool>(argument));
	ht_op.set_tx_rx_mcs_equal(qdbus_cast<bool>(argument));
	ht_op.set_max_tx_spatial_streams(qdbus_cast<unsigned int>(argument));
	ht_op.set_tx_unequal_modulation(qdbus_cast<bool>(argument));
	argument.endStructure();
	return argument;
}
