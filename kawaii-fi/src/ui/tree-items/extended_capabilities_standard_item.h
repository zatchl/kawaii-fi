#ifndef EXTENDED_CAPABILITIES_STANDARD_ITEM_H
#define EXTENDED_CAPABILITIES_STANDARD_ITEM_H

#include <QStandardItem>
#include <libkawaii-fi/ies/extended_capabilities.h>

class ExtendedCapabilitiesStandardItem : public QStandardItem {
public:
	ExtendedCapabilitiesStandardItem(const ExtendedCapabilities &extended_capabilities);
};

#endif // EXTENDED_CAPABILITIES_STANDARD_ITEM_H
