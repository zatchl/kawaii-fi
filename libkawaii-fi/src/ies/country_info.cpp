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
	QByteArray::size_type i = 3;
	while (i + 2 < bytes().size()) {
		const unsigned int first_channel_number = static_cast<std::uint8_t>(bytes()[i++]);
		const unsigned int number_of_channels = static_cast<std::uint8_t>(bytes()[i++]);
		const int max_transmit_power_dbm = static_cast<std::uint8_t>(bytes()[i++]);

		const unsigned int channel_number_delta = (first_channel_number > 14) ? 4 : 1;
		const unsigned int last_channel_number =
		        first_channel_number + (number_of_channels - 1) * channel_number_delta;

		channel_constraints.append({first_channel_number, last_channel_number, number_of_channels,
		                            max_transmit_power_dbm});
	}
	return channel_constraints;
}
