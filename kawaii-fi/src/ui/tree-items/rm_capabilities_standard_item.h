#ifndef RM_CAPABILITIES_STANDARD_ITEM_H
#define RM_CAPABILITIES_STANDARD_ITEM_H

#include <QStandardItem>
#include <libkawaii-fi/ies/rm_capabilities.h>

class RmCapabilitiesStandardItem : public QStandardItem {
public:
	RmCapabilitiesStandardItem(const RmCapabilities &rm_capabilities);
};

#endif // RM_CAPABILITIES_STANDARD_ITEM_H
