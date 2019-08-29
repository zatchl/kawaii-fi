#include "libkawaii-fi/ies/ht_capabilities.h"

#include "libkawaii-fi/ies/information_element.h"

#include <QByteArray>
#include <array>
#include <cstdint>

namespace {
	const std::uint8_t ldpc_coding_capability_mask = 0x1;      // 0000 0001
	const std::uint8_t supported_channel_width_set_mask = 0x2; // 0000 0010
	const std::uint8_t sm_power_save_mask = 0xc;               // 0000 1100
	const std::uint8_t greenfield_ppdu_mask = 0x10;            // 0001 0000
	const std::uint8_t short_gi_20_mhz_mask = 0x20;            // 0010 0000
	const std::uint8_t short_gi_40_mhz_mask = 0x40;            // 0100 0000
	const std::uint8_t tx_stbc_mask = 0x80;                    // 1000 0000
	const std::uint8_t rx_stbc_mask = 0x3;                     // 0000 0011
	const std::uint8_t delayed_block_ack_mask = 0x4;           // 0000 0100
	const std::uint8_t max_amsdu_length_mask = 0x8;            // 0000 1000
	const std::uint8_t dsss_cck_40_mhz_mask = 0x10;            // 0001 0000
	const std::uint8_t psmp_support_mask = 0x20;               // 0010 0000
	const std::uint8_t forty_mhz_intolerant_mask = 0x40;       // 0100 0000
	const std::uint8_t lsig_txop_protection_mask = 0x80;       // 1000 0000
	const std::uint8_t max_ampdu_length_mask = 0x3;            // 0000 0011
	const std::uint8_t mpdu_density_usec_mask = 0x1c;          // 0001 1100
	//	const std::uint8_t
	const std::uint8_t highest_supported_data_rate_mask = 0;
	const std::uint8_t tx_mcs_defined_mask = 0;
	const std::uint8_t tx_rx_mcs_equal_mask = 0;
	const std::uint8_t max_tx_spatial_streams_mask = 0;
	const std::uint8_t tx_unequal_modulation_mask = 0;
	const std::uint8_t pco_support_mask = 0;
	const std::uint8_t pco_transition_time_mask = 0;
	const std::uint8_t mcs_feedback_mask = 0;
	const std::uint8_t htc_support_mask = 0;
	const std::uint8_t rd_responder_mask = 0;
} // namespace

HtCapabilities::HtCapabilities(const InformationElement &ie) : InformationElement(ie.bytes()) {}

bool HtCapabilities::ldpc_coding_capability() const
{
	if (bytes().size() < 1) {
		return false;
	}
	return bytes()[0] & ldpc_coding_capability_mask;
}

HtSupportedChannelWidth HtCapabilities::supported_channel_width_set() const
{
	if (bytes().size() < 1) {
		return HtSupportedChannelWidth::TwentyMhz;
	}
	return (bytes()[0] & supported_channel_width_set_mask)
	               ? HtSupportedChannelWidth::TwentyOrFortyMhz
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
	if (bytes().size() < 1) {
		return false;
	}
	return bytes()[0] & greenfield_ppdu_mask;
}

bool HtCapabilities::short_gi_20_mhz() const
{
	if (bytes().size() < 1) {
		return false;
	}
	return bytes()[0] & short_gi_20_mhz_mask;
}

bool HtCapabilities::short_gi_40_mhz() const
{
	if (bytes().size() < 1) {
		return false;
	}
	return bytes()[0] & short_gi_40_mhz_mask;
}

bool HtCapabilities::tx_stbc() const
{
	if (bytes().size() < 1) {
		return false;
	}
	return bytes()[0] & tx_stbc_mask;
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
	if (bytes().size() < 2) {
		return false;
	}
	return bytes()[1] & delayed_block_ack_mask;
}

unsigned int HtCapabilities::max_amsdu_length() const
{
	if (bytes().size() < 2) {
		return 3839;
	}
	return (bytes()[1] & max_amsdu_length_mask) ? 7935 : 3839;
}

bool HtCapabilities::dsss_cck_40_mhz() const
{
	if (bytes().size() < 2) {
		return false;
	}
	return bytes()[1] & dsss_cck_40_mhz_mask;
}

bool HtCapabilities::psmp_support() const
{
	if (bytes().size() < 2) {
		return false;
	}
	return bytes()[1] & psmp_support_mask;
}

bool HtCapabilities::forty_mhz_intolerant() const
{
	if (bytes().size() < 2) {
		return false;
	}
	return bytes()[1] & forty_mhz_intolerant_mask;
}

bool HtCapabilities::lsig_txop_protection() const
{
	if (bytes().size() < 2) {
		return false;
	}
	return bytes()[1] & lsig_txop_protection_mask;
}

unsigned int HtCapabilities::max_ampdu_length() const
{
	if (bytes().size() < 3) {
		return 8191;
	}
	unsigned int exp = 13 + (bytes()[2] & max_ampdu_length_mask);
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
