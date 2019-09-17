#include "libkawaii-fi/ies/ds_parameter.h"

#include "libkawaii-fi/ies/information_element.h"

#include <QByteArray>

DsParameter::DsParameter(const InformationElement &ie) : InformationElement(ie.bytes()) {}

unsigned int DsParameter::channel() const
{
	constexpr QByteArray::size_type byte_index = 0;
	return byte_to_unsigned_int(byte_index);
}
