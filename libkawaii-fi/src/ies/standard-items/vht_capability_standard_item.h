#ifndef VHT_CAPABILITY_STANDARD_ITEM_H
#define VHT_CAPABILITY_STANDARD_ITEM_H

#include <QStandardItem>

class VhtCapabilities;

class VhtCapabilityStandardItem : public QStandardItem {
public:
	explicit VhtCapabilityStandardItem(const VhtCapabilities &vht_cap);
};

#endif // VHT_CAPABILITY_STANDARD_ITEM_H
