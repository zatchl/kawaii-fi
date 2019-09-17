#include "libkawaii-fi/ies/rm_capabilities.h"

#include "libkawaii-fi/ies/information_element.h"
#include "standard-items/rm_capabilities_standard_item.h"

class QStandardItem;

RmCapabilities::RmCapabilities(const std::string_view &bytes)
    : InformationElement(bytes, WLAN_EID_RRM_ENABLED_CAPABILITIES)
{
}

QStandardItem *RmCapabilities::standard_item() const
{
	return new RmCapabilitiesStandardItem(*this);
}
