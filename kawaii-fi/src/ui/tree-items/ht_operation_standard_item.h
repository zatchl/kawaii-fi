#ifndef HT_OPERATION_STANDARD_ITEM_H
#define HT_OPERATION_STANDARD_ITEM_H

#include <QStandardItem>
#include <libkawaii-fi/ies/ht_operations.h>

class HtOperationStandardItem : public QStandardItem {
public:
	HtOperationStandardItem(const HtOperations &ht_op);
};

#endif // HT_OPERATION_STANDARD_ITEM_H
