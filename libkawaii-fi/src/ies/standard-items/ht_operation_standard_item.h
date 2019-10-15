#ifndef HT_OPERATION_STANDARD_ITEM_H
#define HT_OPERATION_STANDARD_ITEM_H

#include <QStandardItem>

namespace KawaiiFi::Ies {
	class HtOperations;
	class HtOperationStandardItem : public QStandardItem {
	public:
		explicit HtOperationStandardItem(const HtOperations &ht_op);
	};
} // namespace KawaiiFi::Ies

#endif // HT_OPERATION_STANDARD_ITEM_H
