#ifndef TIM_STANDARD_ITEM_H
#define TIM_STANDARD_ITEM_H

#include <QStandardItem>

class TrafficIndicationMap;

class TimStandardItem : public QStandardItem {
public:
	explicit TimStandardItem(const TrafficIndicationMap &tim);
};

#endif // TIM_STANDARD_ITEM_H
