#include "rm_capabilities_standard_item.h"

class RmCapabilities;

namespace KawaiiFi::Ies {
	RmCapabilitiesStandardItem::RmCapabilitiesStandardItem(const RmCapabilities &rm_capabilities)
	    : QStandardItem("RM Enabled Capabilities")
	{
	}
} // namespace KawaiiFi::Ies
