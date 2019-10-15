#include "libkawaii-fi/ies/erp_info.h"

#include "libkawaii-fi/ies/information_element.h"
#include "standard-items/erp_info_standard_item.h"

#include <QByteArray>

class QStandardItem;

namespace KawaiiFi::Ies {
	ErpInfo::ErpInfo(const std::string_view &bytes) : InformationElement(bytes, WLAN_EID_ERP_INFO)
	{
	}

	QStandardItem *ErpInfo::standard_item() const { return new ErpInfoStandardItem(*this); }

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
} // namespace KawaiiFi::Ies
