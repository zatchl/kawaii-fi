#ifndef HT_OPERATION_STANDARD_ITEM_H
#define HT_OPERATION_STANDARD_ITEM_H

#include <QStandardItem>

class HtOperations;

class HtOperationStandardItem : public QStandardItem {
public:
	explicit HtOperationStandardItem(const HtOperations &ht_op);
};

#endif // HT_OPERATION_STANDARD_ITEM_H
