#ifndef EXTENDED_CAPABILITIES_STANDARD_ITEM_H
#define EXTENDED_CAPABILITIES_STANDARD_ITEM_H

#include <QStandardItem>

class ExtendedCapabilities;

class ExtendedCapabilitiesStandardItem : public QStandardItem {
public:
	explicit ExtendedCapabilitiesStandardItem(const ExtendedCapabilities &extended_capabilities);
};

#endif // EXTENDED_CAPABILITIES_STANDARD_ITEM_H
