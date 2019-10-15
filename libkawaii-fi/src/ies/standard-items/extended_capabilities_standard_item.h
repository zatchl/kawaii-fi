#ifndef EXTENDED_CAPABILITIES_STANDARD_ITEM_H
#define EXTENDED_CAPABILITIES_STANDARD_ITEM_H

#include <QStandardItem>

namespace KawaiiFi::Ies {
	class ExtendedCapabilities;
	class ExtendedCapabilitiesStandardItem : public QStandardItem {
	public:
		explicit ExtendedCapabilitiesStandardItem(
		        const ExtendedCapabilities &extended_capabilities);
	};
} // namespace KawaiiFi::Ies

#endif // EXTENDED_CAPABILITIES_STANDARD_ITEM_H
