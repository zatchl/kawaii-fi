#ifndef TIM_STANDARD_ITEM_H
#define TIM_STANDARD_ITEM_H

#include <QStandardItem>

namespace KawaiiFi::Ies {
	class TrafficIndicationMap;
	class TimStandardItem : public QStandardItem {
	public:
		explicit TimStandardItem(const TrafficIndicationMap &tim);
	};
} // namespace KawaiiFi::Ies

#endif // TIM_STANDARD_ITEM_H
