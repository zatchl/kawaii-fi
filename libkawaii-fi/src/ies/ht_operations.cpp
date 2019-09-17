#include "libkawaii-fi/ies/ht_operations.h"

#include "libkawaii-fi/ies/ht_capabilities.h"
#include "libkawaii-fi/ies/information_element.h"

#include <QByteArray>

namespace {
	const unsigned int ht_operation_ie_length = 22;
	const std::uint8_t secondary_channel_offset_mask = 0x3; // 0000 0011
	const std::uint8_t ht_protection_mask = 0x3;            // 0000 0011
} // namespace

HtOperations::HtOperations(const InformationElement &ie) : InformationElement(ie.bytes()) {}

HtOperations::HtOperations(const char *bytes, int size) : InformationElement(bytes, size) {}

unsigned int HtOperations::primary_channel() const
{
	constexpr QByteArray::size_type byte_index = 0;
	return byte_to_unsigned_int(byte_index);
}

SecondaryChannelOffset HtOperations::secondary_channel_offset() const
{
	constexpr QByteArray::size_type byte_index = 1;
	constexpr unsigned int bit_start_index = 0;
	constexpr unsigned int number_of_bits = 2;

	switch (bits_to_unsigned_int(byte_index, bit_start_index, number_of_bits)) {
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
	constexpr QByteArray::size_type byte_index = 1;
	constexpr unsigned int bit_index = 2;
	return bits_to_bool(byte_index, bit_index) ? HtSupportedChannelWidth::TwentyOrFortyMhz
	                                           : HtSupportedChannelWidth::TwentyMhz;
}

bool HtOperations::rifs() const
{
	constexpr unsigned int byte_mask = 1;
	constexpr unsigned int bit_mask = 3;
	return bits_to_bool(byte_mask, bit_mask);
}

HtProtection HtOperations::ht_protection() const
{
	constexpr QByteArray::size_type byte_index = 2;
	constexpr unsigned int bit_start_index = 0;
	constexpr unsigned int number_of_bits = 2;

	switch (bits_to_unsigned_int(byte_index, bit_start_index, number_of_bits)) {
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
	constexpr unsigned int byte_mask = 2;
	constexpr unsigned int bit_mask = 2;
	return bits_to_bool(byte_mask, bit_mask);
}

bool HtOperations::obss_non_ht_stas_present() const
{
	constexpr unsigned int byte_mask = 2;
	constexpr unsigned int bit_mask = 4;
	return bits_to_bool(byte_mask, bit_mask);
}

unsigned int HtOperations::center_freq_segment_two() const { return 0; }

bool HtOperations::dual_beacon() const
{
	constexpr unsigned int byte_mask = 4;
	constexpr unsigned int bit_mask = 6;
	return bits_to_bool(byte_mask, bit_mask);
}

bool HtOperations::dual_cts_protection() const
{
	constexpr unsigned int byte_mask = 4;
	constexpr unsigned int bit_mask = 7;
	return bits_to_bool(byte_mask, bit_mask);
}

bool HtOperations::stbc_beacon() const
{
	constexpr unsigned int byte_mask = 5;
	constexpr unsigned int bit_mask = 0;
	return bits_to_bool(byte_mask, bit_mask);
}

bool HtOperations::lsig_txop_protection_full_support() const
{
	constexpr unsigned int byte_mask = 5;
	constexpr unsigned int bit_mask = 1;
	return bits_to_bool(byte_mask, bit_mask);
}

bool HtOperations::pco_active() const
{
	constexpr unsigned int byte_mask = 5;
	constexpr unsigned int bit_mask = 2;
	return bits_to_bool(byte_mask, bit_mask);
}

PcoPhase HtOperations::pco_phase() const
{
	constexpr unsigned int byte_mask = 5;
	constexpr unsigned int bit_mask = 3;
	return bits_to_bool(byte_mask, bit_mask) ? PcoPhase::FortyMhz : PcoPhase::TwentyMhz;
}

QVector<std::uint8_t> HtOperations::rx_mcs() const { return QVector<std::uint8_t>(); }

unsigned int HtOperations::highest_supported_data_rate() const { return 0; }

bool HtOperations::tx_mcs_defined() const { return false; }

bool HtOperations::tx_rx_mcs_equal() const { return false; }

unsigned int HtOperations::max_tx_spatial_streams() const { return 0; }

bool HtOperations::tx_unequal_modulation() const { return false; }
