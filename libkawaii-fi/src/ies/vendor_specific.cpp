#include "libkawaii-fi/ies/vendor_specific.h"

#include "libkawaii-fi/ies/information_element.h"

#include <QByteArray>
#include <array>

VendorSpecific::VendorSpecific(const InformationElement &ie) : InformationElement(ie.bytes()) {}

std::array<unsigned char, 3> VendorSpecific::oui() const
{
	if (bytes().size() < 3) {
		return {0x0, 0x0, 0x0};
	}
	return {static_cast<unsigned char>(bytes()[0]), static_cast<unsigned char>(bytes()[1]),
	        static_cast<unsigned char>(bytes()[2])};
}

unsigned int VendorSpecific::type() const
{
	if (bytes().size() < 4) {
		return 0;
	}
	return static_cast<unsigned char>(bytes()[3]);
}