#ifndef HT_CAPABILITY_STANDARD_ITEM_H
#define HT_CAPABILITY_STANDARD_ITEM_H

#include <QStandardItem>

class HtCapabilities;

class HtCapabilityStandardItem : public QStandardItem {
public:
	explicit HtCapabilityStandardItem(const HtCapabilities &ht_cap);
};

#endif // HT_CAPABILITY_STANDARD_ITEM_H
