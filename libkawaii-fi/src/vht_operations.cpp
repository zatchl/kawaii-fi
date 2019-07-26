#include "libkawaii-fi/vht_operations.h"

#include "libkawaii-fi/information_element.h"
#include "libkawaii-fi/vht_capabilities.h"

#include <QByteArray>

namespace {
	const unsigned int vht_operation_ie_length = 5;
}

VhtOperations::VhtOperations(const InformationElement &ie) : InformationElement(ie.bytes()) {}

VhtChannelWidth VhtOperations::channel_width() const
{
	if (bytes().size() < 1) {
		return VhtChannelWidth::TwentyOrFortyMhz;
	}
	switch (bytes()[0]) {
	case 0:
		return VhtChannelWidth::TwentyOrFortyMhz;
	case 1:
		return VhtChannelWidth::EightyMhz;
	case 2:
		return VhtChannelWidth::OneSixtyMhz;
	case 3:
		return VhtChannelWidth::EightyPlusEightyMhz;
	default:
		return VhtChannelWidth::TwentyOrFortyMhz;
	}
}

unsigned int VhtOperations::channel_center_segment_zero() const
{
	if (bytes().size() < 2) {
		return 0;
	}
	return static_cast<unsigned char>(bytes()[1]);
}

unsigned int VhtOperations::channel_center_segment_one() const
{
	if (bytes().size() < 3) {
		return 0;
	}
	return static_cast<unsigned char>(bytes()[2]);
}

VhtMcs VhtOperations::mcs_basic_one_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtOperations::mcs_basic_two_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtOperations::mcs_basic_three_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtOperations::mcs_basic_four_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtOperations::mcs_basic_five_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtOperations::mcs_basic_six_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtOperations::mcs_basic_seven_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtOperations::mcs_basic_eight_ss() const { return VhtMcs::NotSupported; }
