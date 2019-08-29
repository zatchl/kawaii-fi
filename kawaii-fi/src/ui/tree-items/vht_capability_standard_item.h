#ifndef VHT_CAPABILITY_STANDARD_ITEM_H
#define VHT_CAPABILITY_STANDARD_ITEM_H

#include <QStandardItem>
#include <libkawaii-fi/ies/vht_capabilities.h>

class VhtCapabilityStandardItem : public QStandardItem {
public:
	VhtCapabilityStandardItem(const VhtCapabilities &vht_cap);
};

#endif // VHT_CAPABILITY_STANDARD_ITEM_H
