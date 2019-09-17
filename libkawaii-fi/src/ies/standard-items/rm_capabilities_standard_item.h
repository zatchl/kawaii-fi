#ifndef RM_CAPABILITIES_STANDARD_ITEM_H
#define RM_CAPABILITIES_STANDARD_ITEM_H

#include <QStandardItem>

class RmCapabilities;

class RmCapabilitiesStandardItem : public QStandardItem {
public:
	explicit RmCapabilitiesStandardItem(const RmCapabilities &rm_capabilities);
};

#endif // RM_CAPABILITIES_STANDARD_ITEM_H
