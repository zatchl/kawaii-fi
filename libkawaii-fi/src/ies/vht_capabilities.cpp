#include "libkawaii-fi/ies/vht_capabilities.h"

#include "libkawaii-fi/ies/information_element.h"

#include <QByteArray>
#include <cstdint>

namespace {
	const std::uint8_t max_mpdu_length_mask = 0b00000011;
	const std::uint8_t supported_channel_width_set_mask = 0b00001100;
	const std::uint8_t rx_ldpc_mask = 0b00010000;
	const std::uint8_t short_gi_80_mhz_mask = 0b00100000;
	const std::uint8_t short_gi_160_mhz_mask = 0b01000000;
	const std::uint8_t tx_stbc_mask = 0b10000000;
	const std::uint8_t rx_stbc_mask = 0b00000111;
	const std::uint8_t su_beamformer_capable_mask = 0b00001000;
	const std::uint8_t su_beamformee_capable_mask = 0b00010000;
	const std::uint8_t beamformee_sts_mask = 0b11100000;
	const std::uint8_t sounding_dimensions_mask = 0b00000111;
	const std::uint8_t mu_beamformer_capable_mask = 0b00001000;
	const std::uint8_t mu_beamformee_capable_mask = 0b00010000;
	const std::uint8_t vht_txop_ps_mask = 0b00100000;
	const std::uint8_t htc_vht_capable_mask = 0b01000000;
	const std::uint8_t max_ampdu_length_first_mask = 0b10000000;
	const std::uint8_t max_ampdu_length_second_mask = 0b00000011;
	const std::uint8_t link_adaptation_mask = 0b00001100;
	const std::uint8_t rx_antenna_pattern_consistent_mask = 0b00010000;
	const std::uint8_t tx_antenna_pattern_consistent_mask = 0b00100000;
	//
	const std::uint8_t mcs_rx_one_ss_mask = 0b00000011;
	const std::uint8_t mcs_rx_two_ss_mask = 0b00001100;
	const std::uint8_t mcs_rx_three_ss_mask = 0b00110000;
	const std::uint8_t mcs_rx_four_ss_mask = 0b11000000;
	const std::uint8_t mcs_rx_five_ss_mask = 0b00000011;
	const std::uint8_t mcs_rx_six_ss_mask = 0b00001100;
	const std::uint8_t mcs_rx_seven_ss_mask = 0b00110000;
	const std::uint8_t mcs_rx_eight_ss_mask = 0b11000000;
	const std::uint8_t rx_highest_long_gi_data_rate_mask = 0b00011111;
	const std::uint8_t max_nsts_total_mask = 0b11100000;
	const std::uint8_t mcs_tx_one_ss_mask = 0b00000011;
	const std::uint8_t mcs_tx_two_ss_mask = 0b00001100;
	const std::uint8_t mcs_tx_three_ss_mask = 0b00110000;
	const std::uint8_t mcs_tx_four_ss_mask = 0b11000000;
	const std::uint8_t mcs_tx_five_ss_mask = 0b00000011;
	const std::uint8_t mcs_tx_six_ss_mask = 0b00001100;
	const std::uint8_t mcs_tx_seven_ss_mask = 0b00110000;
	const std::uint8_t mcs_tx_eight_ss_mask = 0b11000000;
	const std::uint8_t mcs_tx_highest_long_gi_data_rate_mask = 0;
	const std::uint8_t extended_nss_bw_capable_mask = 0b00100000;

} // namespace

VhtCapabilities::VhtCapabilities(const InformationElement &ie) : InformationElement(ie.bytes()) {}

unsigned int VhtCapabilities::max_mpdu_length() const
{
	if (bytes().size() < 1) {
		return 3895;
	}
	switch (bytes()[0] & max_mpdu_length_mask) {
	case 0:
		return 3895;
	case 1:
		return 7991;
	case 2:
		return 11454;
	default:
		return 3895;
	}
}

VhtSupportedChannelWidth VhtCapabilities::supported_channel_width_set() const
{
	if (bytes().size() < 1) {
		return VhtSupportedChannelWidth::NoOneSixtyMhzNoEightyPlusEightyMhz;
	}
	switch ((bytes()[0] & supported_channel_width_set_mask) >> 2) {
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
	if (bytes().size() < 1) {
		return false;
	}
	return bytes()[0] & rx_ldpc_mask;
}

bool VhtCapabilities::short_gi_80_mhz() const
{
	if (bytes().size() < 1) {
		return false;
	}
	return bytes()[0] & short_gi_80_mhz_mask;
}

bool VhtCapabilities::short_gi_160_mhz() const
{
	if (bytes().size() < 1) {
		return false;
	}
	return bytes()[0] & short_gi_160_mhz_mask;
}

bool VhtCapabilities::tx_stbc() const
{
	if (bytes().size() < 1) {
		return false;
	}
	return bytes()[0] & tx_stbc_mask;
}

VhtRxStbc VhtCapabilities::rx_stbc() const
{
	if (bytes().size() < 2) {
		return VhtRxStbc::NotSupported;
	}
	switch (bytes()[1] & rx_stbc_mask) {
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
	if (bytes().size() < 2) {
		return false;
	}
	return bytes()[1] & su_beamformer_capable_mask;
}

bool VhtCapabilities::su_beamformee_capable() const
{
	if (bytes().size() < 2) {
		return false;
	}
	return bytes()[1] & su_beamformee_capable_mask;
}

unsigned int VhtCapabilities::beamformee_sts() const
{
	if (bytes().size() < 2) {
		return 0;
	}
	return static_cast<unsigned int>((bytes()[1] & beamformee_sts_mask) >> 1) + 1;
}

unsigned int VhtCapabilities::sounding_dimensions() const
{
	if (bytes().size() < 3) {
		return 0;
	}
	return static_cast<unsigned int>(bytes()[2] & sounding_dimensions_mask) + 1;
}

bool VhtCapabilities::mu_beamformer_capable() const
{
	if (bytes().size() < 3) {
		return false;
	}
	return bytes()[2] & mu_beamformer_capable_mask;
}

bool VhtCapabilities::mu_beamformee_capable() const
{
	if (bytes().size() < 3) {
		return false;
	}
	return bytes()[2] & mu_beamformee_capable_mask;
}

bool VhtCapabilities::vht_txop_ps() const
{
	if (bytes().size() < 3) {
		return false;
	}
	return bytes()[2] & vht_txop_ps_mask;
}

bool VhtCapabilities::htc_vht_capable() const
{
	if (bytes().size() < 3) {
		return false;
	}
	return bytes()[2] & htc_vht_capable_mask;
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
	if (bytes().size() < 4) {
		return LinkAdaptation::NotSupported;
	}
	switch ((bytes()[3] & link_adaptation_mask) >> 2) {
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
	if (bytes().size() < 4) {
		return false;
	}
	return bytes()[3] & rx_antenna_pattern_consistent_mask;
}

bool VhtCapabilities::tx_antenna_pattern_consistent() const
{
	if (bytes().size() < 4) {
		return false;
	}
	return bytes()[3] & tx_antenna_pattern_consistent_mask;
}

VhtMcs VhtCapabilities::mcs_rx_one_ss() const
{
	if (bytes().size() < 5) {
		return VhtMcs::NotSupported;
	}
	switch (bytes()[4] & mcs_rx_one_ss_mask) {
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

VhtMcs VhtCapabilities::mcs_rx_two_ss() const
{
	if (bytes().size() < 5) {
		return VhtMcs::NotSupported;
	}
	switch ((bytes()[4] & mcs_rx_two_ss_mask) >> 2) {
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

VhtMcs VhtCapabilities::mcs_rx_three_ss() const
{
	if (bytes().size() < 5) {
		return VhtMcs::NotSupported;
	}
	switch ((bytes()[4] & mcs_rx_three_ss_mask) >> 4) {
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

VhtMcs VhtCapabilities::mcs_rx_four_ss() const
{
	if (bytes().size() < 5) {
		return VhtMcs::NotSupported;
	}
	switch ((bytes()[4] & mcs_rx_four_ss_mask) >> 6) {
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

VhtMcs VhtCapabilities::mcs_rx_five_ss() const
{
	if (bytes().size() < 6) {
		return VhtMcs::NotSupported;
	}
	switch (bytes()[5] & mcs_rx_five_ss_mask) {
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

VhtMcs VhtCapabilities::mcs_rx_six_ss() const
{
	if (bytes().size() < 6) {
		return VhtMcs::NotSupported;
	}
	switch ((bytes()[5] & mcs_rx_six_ss_mask) >> 2) {
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

VhtMcs VhtCapabilities::mcs_rx_seven_ss() const
{
	if (bytes().size() < 6) {
		return VhtMcs::NotSupported;
	}
	switch ((bytes()[5] & mcs_rx_seven_ss_mask) >> 4) {
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

VhtMcs VhtCapabilities::mcs_rx_eight_ss() const
{
	if (bytes().size() < 6) {
		return VhtMcs::NotSupported;
	}
	switch ((bytes()[5] & mcs_rx_eight_ss_mask) >> 6) {
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
	if (bytes().size() < 8) {
		return 0;
	}
	return static_cast<std::uint8_t>((bytes()[7] & max_nsts_total_mask) >> 5);
}

VhtMcs VhtCapabilities::mcs_tx_one_ss() const
{
	if (bytes().size() < 9) {
		return VhtMcs::NotSupported;
	}
	switch (bytes()[8] & mcs_tx_one_ss_mask) {
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

VhtMcs VhtCapabilities::mcs_tx_two_ss() const
{

	if (bytes().size() < 9) {
		return VhtMcs::NotSupported;
	}
	switch ((bytes()[8] & mcs_tx_two_ss_mask) >> 2) {
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

VhtMcs VhtCapabilities::mcs_tx_three_ss() const
{
	if (bytes().size() < 9) {
		return VhtMcs::NotSupported;
	}
	switch ((bytes()[8] & mcs_tx_three_ss_mask) >> 4) {
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

VhtMcs VhtCapabilities::mcs_tx_four_ss() const
{
	if (bytes().size() < 9) {
		return VhtMcs::NotSupported;
	}
	switch ((bytes()[8] & mcs_tx_four_ss_mask) >> 6) {
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

VhtMcs VhtCapabilities::mcs_tx_five_ss() const
{
	if (bytes().size() < 10) {
		return VhtMcs::NotSupported;
	}
	switch (bytes()[9] & mcs_tx_five_ss_mask) {
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

VhtMcs VhtCapabilities::mcs_tx_six_ss() const
{
	if (bytes().size() < 10) {
		return VhtMcs::NotSupported;
	}
	switch ((bytes()[9] & mcs_tx_six_ss_mask) >> 2) {
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

VhtMcs VhtCapabilities::mcs_tx_seven_ss() const
{
	if (bytes().size() < 10) {
		return VhtMcs::NotSupported;
	}
	switch ((bytes()[9] & mcs_tx_seven_ss_mask) >> 4) {
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

VhtMcs VhtCapabilities::mcs_tx_eight_ss() const
{
	if (bytes().size() < 10) {
		return VhtMcs::NotSupported;
	}
	switch ((bytes()[9] & mcs_tx_eight_ss_mask) >> 6) {
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

std::array<VhtMcs, 8> VhtCapabilities::mcs_tx() const
{
	return {mcs_tx_one_ss(),  mcs_tx_two_ss(), mcs_tx_three_ss(), mcs_tx_four_ss(),
	        mcs_tx_five_ss(), mcs_tx_six_ss(), mcs_tx_seven_ss(), mcs_tx_eight_ss()};
}

unsigned int VhtCapabilities::tx_highest_long_gi_data_rate() const { return 0; }

bool VhtCapabilities::extended_nss_bw_capable() const
{
	if (bytes().size() < 12) {
		return false;
	}
	return bytes()[11] & extended_nss_bw_capable_mask;
}
