#ifndef VHT_OPERATION_STANDARD_ITEM_H
#define VHT_OPERATION_STANDARD_ITEM_H

#include <QStandardItem>

namespace KawaiiFi::Ies {
	class VhtOperations;
	class VhtOperationStandardItem : public QStandardItem {
	public:
		explicit VhtOperationStandardItem(const VhtOperations &vht_op);
	};
} // namespace KawaiiFi::Ies

#endif // VHT_OPERATION_STANDARD_ITEM_H
