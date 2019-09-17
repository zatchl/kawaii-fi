#include "libkawaii-fi/ies/information_element.h"

#include <QStandardItem>
#include <cstdint>

InformationElement::InformationElement(const std::string_view &bytes, unsigned int ie_id)
    : bytes_(QByteArray(bytes.begin(), static_cast<QByteArray::size_type>(bytes.size()))),
      ie_id_(ie_id)
{
}

const QByteArray &InformationElement::bytes() const { return bytes_; }

QStandardItem *InformationElement::standard_item() const
{
	auto standard_item = new QStandardItem("Unknown IE");
	return standard_item;
}

QString InformationElement::summary() const { return ""; }

bool InformationElement::bits_to_bool(QByteArray::size_type byte_index,
                                      unsigned int bit_index) const
{
	if (bytes_.size() <= byte_index) {
		return false;
	}

	const auto byte_mask = static_cast<std::uint8_t>(1 << bit_index);
	return bytes_[byte_index] & byte_mask;
}

unsigned int InformationElement::byte_to_unsigned_int(QByteArray::size_type byte_index,
                                                      unsigned int default_value) const
{
	constexpr unsigned int bit_start_index = 0;
	constexpr unsigned int number_of_bits = 8;
	return bits_to_unsigned_int(byte_index, bit_start_index, number_of_bits, default_value);
}

unsigned int InformationElement::bits_to_unsigned_int(QByteArray::size_type byte_index,
                                                      unsigned int bit_start_index,
                                                      unsigned int number_of_bits,
                                                      unsigned int default_value) const
{
	if ((bytes_.size() <= byte_index) || (bit_start_index + number_of_bits > 8)) {
		return default_value;
	}

	const unsigned int byte_mask = (1 << number_of_bits) - 1;
	return static_cast<unsigned int>(bytes_[byte_index]) & byte_mask;
}
