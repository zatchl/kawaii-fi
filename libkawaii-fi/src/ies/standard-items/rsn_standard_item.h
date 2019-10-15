#ifndef RSN_STANDARD_ITEM_H
#define RSN_STANDARD_ITEM_H

#include <QStandardItem>

namespace KawaiiFi::Ies {
	class RobustSecurityNetwork;
	class RsnStandardItem : public QStandardItem {
	public:
		explicit RsnStandardItem(const RobustSecurityNetwork &rsn);
	};
} // namespace KawaiiFi::Ies

#endif // RSN_STANDARD_ITEM_H
