#include "libkawaii-fi/ht_operations.h"

#include "libkawaii-fi/ht_capabilities.h"

QDBusArgument &operator<<(QDBusArgument &argument, const HtOperations &ht_op)
{
	argument.beginStructure();
	argument << ht_op.supported << ht_op.primary_channel
	         << static_cast<int>(ht_op.secondary_channel_offset)
	         << static_cast<int>(ht_op.supported_channel_width) << ht_op.rifs
	         << static_cast<int>(ht_op.ht_protection) << ht_op.non_greenfield_stas_present
	         << ht_op.obss_non_ht_stas_present << ht_op.center_freq_segment_two << ht_op.dual_beacon
	         << ht_op.dual_cts_protection << ht_op.stbc_beacon
	         << ht_op.lsig_txop_protection_full_support << ht_op.pco_active
	         << static_cast<int>(ht_op.pco_phase) << ht_op.rx_mcs
	         << ht_op.highest_supported_data_rate << ht_op.tx_mcs_defined << ht_op.tx_rx_mcs_equal
	         << ht_op.max_tx_spatial_streams << ht_op.tx_unequal_modulation;
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, HtOperations &ht_op)
{
	int secondary_channel_offset = 0;
	int supported_channel_width = 0;
	int ht_protection = 0;
	int pco_phase = 0;
	argument.beginStructure();
	argument >> ht_op.supported >> ht_op.primary_channel >> secondary_channel_offset >>
	        supported_channel_width >> ht_op.rifs >> ht_protection >>
	        ht_op.non_greenfield_stas_present >> ht_op.obss_non_ht_stas_present >>
	        ht_op.center_freq_segment_two >> ht_op.dual_beacon >> ht_op.dual_cts_protection >>
	        ht_op.stbc_beacon >> ht_op.lsig_txop_protection_full_support >> ht_op.pco_active >>
	        pco_phase >> ht_op.rx_mcs >> ht_op.highest_supported_data_rate >>
	        ht_op.tx_mcs_defined >> ht_op.tx_rx_mcs_equal >> ht_op.max_tx_spatial_streams >>
	        ht_op.tx_unequal_modulation;
	argument.endStructure();
	ht_op.secondary_channel_offset = static_cast<SecondaryChannelOffset>(secondary_channel_offset);
	ht_op.supported_channel_width = static_cast<HtSupportedChannelWidth>(supported_channel_width);
	ht_op.ht_protection = static_cast<HtProtection>(ht_protection);
	ht_op.pco_phase = static_cast<PcoPhase>(pco_phase);
	return argument;
}
