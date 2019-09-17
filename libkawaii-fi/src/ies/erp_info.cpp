#include "libkawaii-fi/ies/erp_info.h"

#include "libkawaii-fi/ies/information_element.h"

#include <QByteArray>

ErpInfo::ErpInfo(const InformationElement &ie) : InformationElement(ie.bytes()) {}

bool ErpInfo::non_erp_present() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_index = 0;
	return bits_to_bool(byte_index, bit_index);
}

bool ErpInfo::use_protection() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_index = 1;
	return bits_to_bool(byte_index, bit_index);
}

bool ErpInfo::barker_preamble_mode() const
{
	constexpr QByteArray::size_type byte_index = 0;
	constexpr unsigned int bit_index = 2;
	return bits_to_bool(byte_index, bit_index);
}
