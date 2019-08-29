#include "rm_capabilities_standard_item.h"

#include <libkawaii-fi/ies/rm_capabilities.h>

RmCapabilitiesStandardItem::RmCapabilitiesStandardItem(const RmCapabilities &rm_capabilities)
    : QStandardItem("RM Enabled Capabilities")
{
}
