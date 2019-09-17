#include "libkawaii-fi/ies/ds_parameter.h"

#include "libkawaii-fi/ies/information_element.h"

#include <QByteArray>
#include <QStandardItem>

DsParameter::DsParameter(const std::string_view &bytes)
    : InformationElement(bytes, WLAN_EID_DS_PARAMS)
{
}

QStandardItem *DsParameter::standard_item() const
{
	auto standard_item = new QStandardItem("DS Parameters");
	return standard_item;
}

QString DsParameter::summary() const { return QString("Channel %0").arg(channel()); }

unsigned int DsParameter::channel() const
{
	constexpr QByteArray::size_type byte_index = 0;
	return byte_to_unsigned_int(byte_index);
}
