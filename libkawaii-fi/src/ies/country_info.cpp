#include "libkawaii-fi/ies/country_info.h"

#include "libkawaii-fi/ies/information_element.h"
#include "standard-items/country_info_standard_item.h"

#include <QByteArray>
#include <cstdint>

class QStandardItem;

CountryInfo::CountryInfo(const std::string_view &bytes)
    : InformationElement(bytes, WLAN_EID_COUNTRY)
{
}

QStandardItem *CountryInfo::standard_item() const { return new CountryInfoStandardItem(*this); }

QString CountryInfo::summary() const { return country_code(); }

QString CountryInfo::country_code() const
{
	constexpr QByteArray::size_type first_char_byte_index = 0;
	constexpr QByteArray::size_type second_char_byte_index = 1;

	if (bytes().size() <= second_char_byte_index) {
		return "";
	}

	return QString("%0%1").arg(bytes()[first_char_byte_index]).arg(bytes()[second_char_byte_index]);
}

Environment CountryInfo::environment() const
{
	constexpr QByteArray::size_type environment_byte_index = 2;

	switch (byte_to_unsigned_int(environment_byte_index)) {
	case ' ':
		return Environment::Any;
	case 'I':
	case 'i':
		return Environment::Indoor;
	case 'O':
	case 'o':
		return Environment::Outdoor;
	default:
		return Environment::Any;
	}
}

QVector<ChannelPowerConstraint> CountryInfo::channel_constraints() const
{
	QVector<ChannelPowerConstraint> channel_constraints;
	auto it = bytes().begin() + 3;
	while (it + 3 < bytes().end()) {
		channel_constraints.append({static_cast<std::uint8_t>(*it),
		                            static_cast<std::uint8_t>(*(it + 1)),
		                            static_cast<std::uint8_t>(*(it + 2))});
		it += 3;
	}
	return channel_constraints;
}
