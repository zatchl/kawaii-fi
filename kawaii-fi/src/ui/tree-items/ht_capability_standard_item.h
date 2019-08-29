#ifndef HT_CAPABILITY_STANDARD_ITEM_H
#define HT_CAPABILITY_STANDARD_ITEM_H

#include <QStandardItem>
#include <libkawaii-fi/ies/ht_capabilities.h>

class HtCapabilityStandardItem : public QStandardItem {
public:
	HtCapabilityStandardItem(const HtCapabilities &ht_cap);
};

#endif // HT_CAPABILITY_STANDARD_ITEM_H
