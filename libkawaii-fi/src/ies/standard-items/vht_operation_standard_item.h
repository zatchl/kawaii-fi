#ifndef VHT_OPERATION_STANDARD_ITEM_H
#define VHT_OPERATION_STANDARD_ITEM_H

#include <QStandardItem>

class VhtOperations;

class VhtOperationStandardItem : public QStandardItem {
public:
	explicit VhtOperationStandardItem(const VhtOperations &vht_op);
};

#endif // VHT_OPERATION_STANDARD_ITEM_H
