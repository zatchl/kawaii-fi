#include "libkawaii-fi/ies/erp_info.h"

#include "libkawaii-fi/ies/information_element.h"

#include <QByteArray>

ErpInfo::ErpInfo(const InformationElement &ie) : InformationElement(ie.bytes()) {}

bool ErpInfo::non_erp_present() const
{
	if (bytes().size() > 1) {
		return false;
	}
	return bytes()[0] & 0b00000001;
}

bool ErpInfo::use_protection() const
{
	if (bytes().size() > 1) {
		return false;
	}
	return bytes()[0] & 0b00000010;
}

bool ErpInfo::barker_preamble_mode() const
{
	if (bytes().size() > 1) {
		return false;
	}
	return bytes()[0] & 0b00000100;
}
