#include "libkawaii-fi/ies/vht_operations.h"

#include "libkawaii-fi/ies/information_element.h"
#include "libkawaii-fi/ies/vht_capabilities.h"
#include "standard-items/vht_operation_standard_item.h"

#include <QByteArray>

class QStandardItem;

VhtOperations::VhtOperations(const std::string_view &bytes)
    : InformationElement(bytes, WLAN_EID_VHT_OPERATION)
{
}

QStandardItem *VhtOperations::standard_item() const { return new VhtOperationStandardItem(*this); }

VhtChannelWidth VhtOperations::channel_width() const
{
	constexpr QByteArray::size_type byte_index = 0;

	switch (byte_to_unsigned_int(byte_index)) {
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
	constexpr QByteArray::size_type byte_index = 1;
	return byte_to_unsigned_int(byte_index);
}

unsigned int VhtOperations::channel_center_segment_one() const
{
	constexpr QByteArray::size_type byte_index = 2;
	return byte_to_unsigned_int(byte_index);
}

VhtMcs VhtOperations::mcs_basic_one_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtOperations::mcs_basic_two_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtOperations::mcs_basic_three_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtOperations::mcs_basic_four_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtOperations::mcs_basic_five_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtOperations::mcs_basic_six_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtOperations::mcs_basic_seven_ss() const { return VhtMcs::NotSupported; }

VhtMcs VhtOperations::mcs_basic_eight_ss() const { return VhtMcs::NotSupported; }
