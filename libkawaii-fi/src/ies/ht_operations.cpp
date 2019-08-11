#include "libkawaii-fi/ies/ht_operations.h"

#include "libkawaii-fi/ies/ht_capabilities.h"
#include "libkawaii-fi/ies/information_element.h"

#include <QByteArray>

namespace {
	const unsigned int ht_operation_ie_length = 22;
	const std::uint8_t secondary_channel_offset_mask = 0x3;          // 0000 0011
	const std::uint8_t supported_channel_width_mask = 0x4;           // 0000 0100
	const std::uint8_t rifs_mask = 0x8;                              // 0000 1000
	const std::uint8_t ht_protection_mask = 0x3;                     // 0000 0011
	const std::uint8_t non_greenfield_stas_present_mask = 0x4;       // 0000 0100
	const std::uint8_t obss_non_ht_stas_present_mask = 0x10;         // 0001 0000
	const std::uint8_t dual_beacon_mask = 0x40;                      // 0100 0000
	const std::uint8_t dual_cts_protection_mask = 0x80;              // 1000 0000
	const std::uint8_t stbc_beacon_mask = 0x1;                       // 0000 0001
	const std::uint8_t lsig_txop_protection_full_support_mask = 0x2; // 0000 0010
	const std::uint8_t pco_active_mask = 0x4;                        // 0000 0100
	const std::uint8_t pco_phase_mask = 0x8;                         // 0000 1000
} // namespace

HtOperations::HtOperations(const InformationElement &ie) : InformationElement(ie.bytes()) {}

HtOperations::HtOperations(const char *bytes, int size) : InformationElement(bytes, size) {}

unsigned int HtOperations::primary_channel() const
{
	if (bytes().size() < 1) {
		return 0;
	}
	return static_cast<unsigned char>(bytes()[0]);
}

SecondaryChannelOffset HtOperations::secondary_channel_offset() const
{
	if (bytes().size() < 2) {
		return SecondaryChannelOffset::NoSecondaryChannel;
	}
	switch (bytes()[1] & secondary_channel_offset_mask) {
	case 0:
		return SecondaryChannelOffset::NoSecondaryChannel;
	case 1:
		return SecondaryChannelOffset::Above;
	case 3:
		return SecondaryChannelOffset::Below;
	default:
		return SecondaryChannelOffset::NoSecondaryChannel;
	}
}

HtSupportedChannelWidth HtOperations::supported_channel_width() const
{
	if (bytes().size() < 2) {
		return HtSupportedChannelWidth::TwentyMhz;
	}
	return (bytes()[1] & supported_channel_width_mask) ? HtSupportedChannelWidth::TwentyOrFortyMhz
	                                                   : HtSupportedChannelWidth::TwentyMhz;
}

bool HtOperations::rifs() const
{
	if (bytes().size() < 2) {
		return false;
	}
	return bytes()[1] & rifs_mask;
}

HtProtection HtOperations::ht_protection() const
{
	if (bytes().size() < 3) {
		return HtProtection::None;
	}
	switch (bytes()[2] & ht_protection_mask) {
	case 0:
		return HtProtection::None;
	case 1:
		return HtProtection::Nonmember;
	case 2:
		return HtProtection::TwentyMhz;
	case 3:
		return HtProtection::NonHtMixed;
	default:
		return HtProtection::None;
	}
}

bool HtOperations::non_greenfield_stas_present() const
{
	if (bytes().size() < 3) {
		return false;
	}
	return bytes()[2] & non_greenfield_stas_present_mask;
}

bool HtOperations::obss_non_ht_stas_present() const
{
	if (bytes().size() < 3) {
		return false;
	}
	return bytes()[2] & obss_non_ht_stas_present_mask;
}

unsigned int HtOperations::center_freq_segment_two() const { return 0; }

bool HtOperations::dual_beacon() const
{
	if (bytes().size() < 5) {
		return false;
	}
	return bytes()[4] & dual_beacon_mask;
}

bool HtOperations::dual_cts_protection() const
{
	if (bytes().size() < 5) {
		return false;
	}
	return bytes()[4] & dual_cts_protection_mask;
}

bool HtOperations::stbc_beacon() const
{
	if (bytes().size() < 6) {
		return false;
	}
	return bytes()[5] & stbc_beacon_mask;
}

bool HtOperations::lsig_txop_protection_full_support() const
{
	if (bytes().size() < 6) {
		return false;
	}
	return bytes()[5] & lsig_txop_protection_full_support_mask;
}

bool HtOperations::pco_active() const
{
	if (bytes().size() < 6) {
		return false;
	}
	return bytes()[5] & pco_active_mask;
}

PcoPhase HtOperations::pco_phase() const
{
	if (bytes().size() < 6) {
		return PcoPhase::TwentyMhz;
	}
	return (bytes()[5] & pco_phase_mask) ? PcoPhase::FortyMhz : PcoPhase::TwentyMhz;
}

QVector<std::uint8_t> HtOperations::rx_mcs() const { return QVector<std::uint8_t>(); }

unsigned int HtOperations::highest_supported_data_rate() const { return 0; }

bool HtOperations::tx_mcs_defined() const { return false; }

bool HtOperations::tx_rx_mcs_equal() const { return false; }

unsigned int HtOperations::max_tx_spatial_streams() const { return 0; }

bool HtOperations::tx_unequal_modulation() const { return false; }
