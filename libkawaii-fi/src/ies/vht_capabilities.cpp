#include "libkawaii-fi/ies/vht_capabilities.h"

#include "libkawaii-fi/ies/information_element.h"
#include "standard-items/vht_capability_standard_item.h"

#include <QByteArray>
#include <cstdint>

class QStandardItem;

namespace {
	const std::uint8_t max_ampdu_length_first_mask = 0b10000000;
	const std::uint8_t max_ampdu_length_second_mask = 0b00000011;
	//
	const std::uint8_t rx_highest_long_gi_data_rate_mask = 0b00011111;
	const std::uint8_t mcs_tx_highest_long_gi_data_rate_mask = 0;

	constexpr int mcs_rx_one_to_four_ss_byte_index = 4;
	constexpr int mcs_rx_five_to_eight_ss_byte_index = 5;
	constexpr int mcs_tx_one_to_four_ss_byte_index = 8;
	constexpr int mcs_tx_five_to_eight_ss_byte_index = 9;

} // namespace

VhtCapabilities::VhtCapabilities(const std::string_view &bytes)
    : InformationElement(bytes, WLAN_EID_VHT_CAPABILITY)
{
}

QStandardItem *VhtCapabilities::standard_item() const
{
	return new VhtCapabilityStandardItem(*this);
}

unsigned int VhtCapabilities::max_mpdu_length() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_start_index = 0;
	constexpr unsigned int number_of_bits = 2;
	constexpr unsigned int default_max_mpdu_length = 3895;

	switch (bits_to_unsigned_int(byte_index, bit_start_index, number_of_bits)) {
	case 0:
		return default_max_mpdu_length;
	case 1:
		return 7991;
	case 2:
		return 11454;
	default:
		return default_max_mpdu_length;
	}
}

VhtSupportedChannelWidth VhtCapabilities::supported_channel_width_set() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_start_index = 2;
	constexpr unsigned int number_of_bits = 2;

	switch (bits_to_unsigned_int(byte_index, bit_start_index, number_of_bits)) {
	case 0:
		return VhtSupportedChannelWidth::NoOneSixtyMhzNoEightyPlusEightyMhz;
	case 1:
		return VhtSupportedChannelWidth::OneSixtyMhz;
	case 2:
		return VhtSupportedChannelWidth::OneSixtyMhzEightyPlusEightyMhz;
	default:
		return VhtSupportedChannelWidth::NoOneSixtyMhzNoEightyPlusEightyMhz;
	}
}

bool VhtCapabilities::rx_ldpc() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_index = 4;
	return bits_to_bool(byte_index, bit_index);
}

bool VhtCapabilities::short_gi_80_mhz() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_index = 5;
	return bits_to_bool(byte_index, bit_index);
}

bool VhtCapabilities::short_gi_160_mhz() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_index = 6;
	return bits_to_bool(byte_index, bit_index);
}

bool VhtCapabilities::tx_stbc() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_index = 7;
	return bits_to_bool(byte_index, bit_index);
}

VhtRxStbc VhtCapabilities::rx_stbc() const
{
	constexpr QByteArray::size_type byte_index = 1;
	constexpr unsigned int bit_start_index = 0;
	constexpr unsigned int number_of_bits = 3;

	switch (bits_to_unsigned_int(byte_index, bit_start_index, number_of_bits)) {
	case 0:
		return VhtRxStbc::NotSupported;
	case 1:
		return VhtRxStbc::OneSpatialStream;
	case 2:
		return VhtRxStbc::TwoSpatialStreams;
	case 3:
		return VhtRxStbc::ThreeSpatialStreams;
	case 4:
		return VhtRxStbc::FourSpatialStreams;
	default:
		return VhtRxStbc::NotSupported;
	}
}

bool VhtCapabilities::su_beamformer_capable() const
{
	constexpr QByteArray::size_type byte_index = 1;
	constexpr unsigned int bit_index = 3;
	return bits_to_bool(byte_index, bit_index);
}

bool VhtCapabilities::su_beamformee_capable() const
{
	constexpr QByteArray::size_type byte_index = 1;
	constexpr unsigned int bit_index = 4;
	return bits_to_bool(byte_index, bit_index);
}

unsigned int VhtCapabilities::beamformee_sts() const
{
	constexpr QByteArray::size_type byte_index = 1;
	constexpr unsigned int bit_start_index = 5;
	constexpr unsigned int number_of_bits = 3;

	return bits_to_unsigned_int(byte_index, bit_start_index, number_of_bits) + 1;
}

unsigned int VhtCapabilities::sounding_dimensions() const
{
	constexpr QByteArray::size_type byte_index = 2;
	constexpr unsigned int bit_start_index = 0;
	constexpr unsigned int number_of_bits = 3;

	return bits_to_unsigned_int(byte_index, bit_start_index, number_of_bits) + 1;
}

bool VhtCapabilities::mu_beamformer_capable() const
{
	constexpr QByteArray::size_type byte_index = 2;
	constexpr unsigned int bit_index = 3;
	return bits_to_bool(byte_index, bit_index);
}

bool VhtCapabilities::mu_beamformee_capable() const
{
	constexpr QByteArray::size_type byte_index = 2;
	constexpr unsigned int bit_index = 4;
	return bits_to_bool(byte_index, bit_index);
}

bool VhtCapabilities::vht_txop_ps() const
{
	constexpr QByteArray::size_type byte_index = 2;
	constexpr unsigned int bit_index = 5;
	return bits_to_bool(byte_index, bit_index);
}

bool VhtCapabilities::htc_vht_capable() const
{
	constexpr QByteArray::size_type byte_index = 2;
	constexpr unsigned int bit_index = 6;
	return bits_to_bool(byte_index, bit_index);
}

unsigned int VhtCapabilities::max_ampdu_length() const
{
	if (bytes().size() < 4) {
		return 0;
	}
	unsigned int exp =
	        13 + ((bytes()[2] & max_ampdu_length_first_mask) >> 7) +
	        static_cast<unsigned int>(((bytes()[3] & max_ampdu_length_second_mask) << 1));
	return (1 << exp) - 1;
}

LinkAdaptation VhtCapabilities::link_adaptation() const
{
	constexpr QByteArray::size_type byte_index = 3;
	constexpr unsigned int bit_start_index = 2;
	constexpr unsigned int number_of_bits = 2;

	switch (bits_to_unsigned_int(byte_index, bit_start_index, number_of_bits)) {
	case 0:
		return LinkAdaptation::NotSupported;
	case 2:
		return LinkAdaptation::SupportedUnsolicited;
	case 3:
		return LinkAdaptation::SupportedResponseUnsolicited;
	default:
		return LinkAdaptation::NotSupported;
	}
}

bool VhtCapabilities::rx_antenna_pattern_consistent() const
{
	constexpr QByteArray::size_type byte_index = 3;
	constexpr unsigned int bit_index = 4;
	return bits_to_bool(byte_index, bit_index);
}

bool VhtCapabilities::tx_antenna_pattern_consistent() const
{
	constexpr QByteArray::size_type byte_index = 3;
	constexpr unsigned int bit_index = 5;
	return bits_to_bool(byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_rx_one_ss() const
{
	constexpr unsigned int bit_index = 0;
	return bits_to_vht_mcs(mcs_rx_one_to_four_ss_byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_rx_two_ss() const
{
	constexpr unsigned int bit_index = 2;
	return bits_to_vht_mcs(mcs_rx_one_to_four_ss_byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_rx_three_ss() const
{
	constexpr unsigned int bit_index = 4;
	return bits_to_vht_mcs(mcs_rx_one_to_four_ss_byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_rx_four_ss() const
{
	constexpr unsigned int bit_index = 6;
	return bits_to_vht_mcs(mcs_rx_one_to_four_ss_byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_rx_five_ss() const
{
	constexpr unsigned int bit_index = 0;
	return bits_to_vht_mcs(mcs_rx_five_to_eight_ss_byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_rx_six_ss() const
{
	constexpr unsigned int bit_index = 2;
	return bits_to_vht_mcs(mcs_rx_five_to_eight_ss_byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_rx_seven_ss() const
{
	constexpr unsigned int bit_index = 4;
	return bits_to_vht_mcs(mcs_rx_five_to_eight_ss_byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_rx_eight_ss() const
{
	constexpr unsigned int bit_index = 6;
	return bits_to_vht_mcs(mcs_rx_five_to_eight_ss_byte_index, bit_index);
}

std::array<VhtMcs, 8> VhtCapabilities::mcs_rx() const
{
	return {mcs_rx_one_ss(),  mcs_rx_two_ss(), mcs_rx_three_ss(), mcs_rx_four_ss(),
	        mcs_rx_five_ss(), mcs_rx_six_ss(), mcs_rx_seven_ss(), mcs_rx_eight_ss()};
}

unsigned int VhtCapabilities::rx_highest_long_gi_data_rate() const
{
	if (bytes().size() < 8) {
		return 0;
	}
	return static_cast<std::uint8_t>(bytes()[6]) +
	       static_cast<std::uint8_t>(((bytes()[7] & rx_highest_long_gi_data_rate_mask) << 8));
}

unsigned int VhtCapabilities::max_nsts_total() const
{
	constexpr QByteArray::size_type byte_index = 7;
	constexpr unsigned int bit_start_index = 5;
	constexpr unsigned int number_of_bits = 3;

	return bits_to_unsigned_int(byte_index, bit_start_index, number_of_bits);
}

VhtMcs VhtCapabilities::mcs_tx_one_ss() const
{
	constexpr unsigned int bit_index = 0;
	return bits_to_vht_mcs(mcs_tx_one_to_four_ss_byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_tx_two_ss() const
{
	constexpr unsigned int bit_index = 2;
	return bits_to_vht_mcs(mcs_tx_one_to_four_ss_byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_tx_three_ss() const
{
	constexpr unsigned int bit_index = 4;
	return bits_to_vht_mcs(mcs_tx_one_to_four_ss_byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_tx_four_ss() const
{
	constexpr unsigned int bit_index = 6;
	return bits_to_vht_mcs(mcs_tx_one_to_four_ss_byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_tx_five_ss() const
{
	constexpr unsigned int bit_index = 0;
	return bits_to_vht_mcs(mcs_tx_five_to_eight_ss_byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_tx_six_ss() const
{
	constexpr unsigned int bit_index = 2;
	return bits_to_vht_mcs(mcs_tx_five_to_eight_ss_byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_tx_seven_ss() const
{
	constexpr unsigned int bit_index = 4;
	return bits_to_vht_mcs(mcs_tx_five_to_eight_ss_byte_index, bit_index);
}

VhtMcs VhtCapabilities::mcs_tx_eight_ss() const
{
	constexpr unsigned int bit_index = 6;
	return bits_to_vht_mcs(mcs_tx_five_to_eight_ss_byte_index, bit_index);
}

std::array<VhtMcs, 8> VhtCapabilities::mcs_tx() const
{
	return {mcs_tx_one_ss(),  mcs_tx_two_ss(), mcs_tx_three_ss(), mcs_tx_four_ss(),
	        mcs_tx_five_ss(), mcs_tx_six_ss(), mcs_tx_seven_ss(), mcs_tx_eight_ss()};
}

unsigned int VhtCapabilities::tx_highest_long_gi_data_rate() const { return 0; }

bool VhtCapabilities::extended_nss_bw_capable() const
{
	constexpr QByteArray::size_type byte_index = 11;
	constexpr unsigned int bit_index = 5;
	return bits_to_bool(byte_index, bit_index);
}

VhtMcs VhtCapabilities::bits_to_vht_mcs(int byte_index, unsigned int bit_index) const
{
	// Each MCS is represented by two consecutive bits in a byte
	// 0b00[10]1111 or 0b0000[11]11 (bit index of 4 and 2)
	// First we shift the bits to the front of the byte using the supplied bit index
	// Then we bitwise AND the resulting byte to leave only the first two bits
	//	const auto vht_mcs_byte_mask =
	//	        static_cast<std::uint8_t>(0b00000011 << static_cast<int>(bit_index));
	//	switch (bytes()[byte_index] & vht_mcs_byte_mask) {
	constexpr unsigned int number_of_bits = 2;
	constexpr unsigned int default_value = 3;

	switch (bits_to_unsigned_int(byte_index, bit_index, number_of_bits, default_value)) {
	case 0:
		return VhtMcs::OneThroughSeven;
	case 1:
		return VhtMcs::OneThroughEight;
	case 2:
		return VhtMcs::OneThroughNine;
	default:
		return VhtMcs::NotSupported;
	}
}
