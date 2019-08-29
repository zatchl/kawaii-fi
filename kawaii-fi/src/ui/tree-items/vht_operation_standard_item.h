#ifndef VHT_OPERATION_STANDARD_ITEM_H
#define VHT_OPERATION_STANDARD_ITEM_H

#include <QStandardItem>
#include <libkawaii-fi/ies/vht_operations.h>

class VhtOperationStandardItem : public QStandardItem {
public:
	VhtOperationStandardItem(const VhtOperations &vht_op);
};

#endif // VHT_OPERATION_STANDARD_ITEM_H
