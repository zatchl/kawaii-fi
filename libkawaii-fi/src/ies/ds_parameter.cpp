#include "libkawaii-fi/ies/ds_parameter.h"

#include "libkawaii-fi/ies/information_element.h"

#include <QByteArray>

DsParameter::DsParameter(const InformationElement &ie) : InformationElement(ie.bytes()) {}

unsigned int DsParameter::channel() const
{
	return (bytes().size() >= 1) ? static_cast<unsigned char>(bytes()[0]) : 0;
}
