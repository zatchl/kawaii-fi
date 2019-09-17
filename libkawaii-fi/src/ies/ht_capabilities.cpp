#include "libkawaii-fi/ies/ht_capabilities.h"

#include "libkawaii-fi/ies/information_element.h"
#include "standard-items/ht_capability_standard_item.h"

#include <QByteArray>
#include <array>
#include <cstdint>
#include <string_view>

class QStandardItem;

namespace {
	const std::uint8_t sm_power_save_mask = 0xc;      // 0000 1100
	const std::uint8_t rx_stbc_mask = 0x3;            // 0000 0011
	const std::uint8_t max_ampdu_length_mask = 0x3;   // 0000 0011
	const std::uint8_t mpdu_density_usec_mask = 0x1c; // 0001 1100
} // namespace

HtCapabilities::HtCapabilities(const std::string_view &bytes)
    : InformationElement(bytes, WLAN_EID_HT_CAPABILITY)
{
}

QStandardItem *HtCapabilities::standard_item() const { return new HtCapabilityStandardItem(*this); }

bool HtCapabilities::ldpc_coding_capability() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_index = 0;
	return bits_to_bool(byte_index, bit_index);
}

HtSupportedChannelWidth HtCapabilities::supported_channel_width_set() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_index = 1;
	return bits_to_bool(byte_index, bit_index) ? HtSupportedChannelWidth::TwentyOrFortyMhz
	                                           : HtSupportedChannelWidth::TwentyMhz;
}

SmPowerSave HtCapabilities::sm_power_save() const
{
	if (bytes().size() < 1) {
		return SmPowerSave::Disabled;
	}
	switch ((bytes()[0] & sm_power_save_mask) >> 2) {
	case 0:
		return SmPowerSave::Static;
	case 1:
		return SmPowerSave::Dynamic;
	default:
		return SmPowerSave::Disabled;
	}
}

bool HtCapabilities::greenfield_ppdu() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_index = 4;
	return bits_to_bool(byte_index, bit_index);
}

bool HtCapabilities::short_gi_20_mhz() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_index = 5;
	return bits_to_bool(byte_index, bit_index);
}

bool HtCapabilities::short_gi_40_mhz() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_index = 6;
	return bits_to_bool(byte_index, bit_index);
}

bool HtCapabilities::tx_stbc() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_index = 7;
	return bits_to_bool(byte_index, bit_index);
}

HtRxStbc HtCapabilities::rx_stbc() const
{
	if (bytes().size() < 2) {
		return HtRxStbc::Disabled;
	}
	switch (bytes()[1] & rx_stbc_mask) {
	case 0:
		return HtRxStbc::Disabled;
	case 1:
		return HtRxStbc::OneSpatialStream;
	case 2:
		return HtRxStbc::TwoSpatialStreams;
	case 3:
		return HtRxStbc::ThreeSpatialStreams;
	default:
		return HtRxStbc::Disabled;
	}
}

bool HtCapabilities::delayed_block_ack() const
{
	constexpr QByteArray::size_type byte_index = 1;
	constexpr unsigned int bit_index = 2;
	return bits_to_bool(byte_index, bit_index);
}

unsigned int HtCapabilities::max_amsdu_length() const
{
	constexpr QByteArray::size_type byte_index = 1;
	constexpr unsigned int bit_index = 3;
	return bits_to_bool(byte_index, bit_index) ? 7935 : 3839;
}

bool HtCapabilities::dsss_cck_40_mhz() const
{
	constexpr QByteArray::size_type byte_index = 1;
	constexpr unsigned int bit_index = 4;
	return bits_to_bool(byte_index, bit_index);
}

bool HtCapabilities::psmp_support() const
{
	constexpr QByteArray::size_type byte_index = 1;
	constexpr unsigned int bit_index = 5;
	return bits_to_bool(byte_index, bit_index);
}

bool HtCapabilities::forty_mhz_intolerant() const
{
	constexpr QByteArray::size_type byte_index = 1;
	constexpr unsigned int bit_index = 6;
	return bits_to_bool(byte_index, bit_index);
}

bool HtCapabilities::lsig_txop_protection() const
{
	constexpr QByteArray::size_type byte_index = 1;
	constexpr unsigned int bit_index = 7;

	return bits_to_bool(byte_index, bit_index);
}

unsigned int HtCapabilities::max_ampdu_length() const
{
	constexpr QByteArray::size_type byte_index = 2;
	constexpr unsigned int default_max_ampdu_length = 8191;

	if (bytes().size() <= byte_index) {
		return default_max_ampdu_length;
	}

	const unsigned int exp = 13 + (bytes()[byte_index] & max_ampdu_length_mask);
	return (1 << exp) - 1;
}

double HtCapabilities::mpdu_density_usec() const
{
	if (bytes().size() < 3) {
		return 0;
	}
	switch ((bytes()[2] & mpdu_density_usec_mask) >> 2) {
	case 0:
		return 0;
	case 1:
		return 0.25;
	case 2:
		return 0.5;
	case 3:
		return 1;
	case 4:
		return 2;
	case 5:
		return 4;
	case 6:
		return 8;
	case 7:
		return 16;
	default:
		return 0;
	}
}

std::array<HtMcs, 4> HtCapabilities::rx_mcs() const
{
	if (bytes().size() < 7) {
		return {};
	}

	std::array<HtMcs, 4> rx_mcs;
	for (unsigned int i = 0; i < 4; ++i) {
		std::uint8_t mcs_ss = static_cast<std::uint8_t>(bytes()[3 + i]);
		if (!mcs_ss) {
			rx_mcs[i] = {HtModulation::None, 0};
			continue;
		}
		int highest_set_bit = 0;
		while (mcs_ss >>= 1) {
			++highest_set_bit;
		}
		switch (highest_set_bit) {
		case 0:
			rx_mcs[i] = {HtModulation::BPSK, 0.5};
			break;
		case 1:
			rx_mcs[i] = {HtModulation::QPSK, 0.5};
			break;
		case 2:
			rx_mcs[i] = {HtModulation::QPSK, 0.75};
			break;
		case 3:
			rx_mcs[i] = {HtModulation::QAM_16, 0.5};
			break;
		case 4:
			rx_mcs[i] = {HtModulation::QAM_16, 0.75};
			break;
		case 5:
			rx_mcs[i] = {HtModulation::QAM_64, 2.0 / 3};
			break;
		case 6:
			rx_mcs[i] = {HtModulation::QAM_64, 0.75};
			break;
		case 7:
			rx_mcs[i] = {HtModulation::QAM_64, 5.0 / 6};
			break;
		default:
			rx_mcs[i] = {HtModulation::None, 0};
			break;
		}
	}
	return rx_mcs;
}

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
