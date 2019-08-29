#ifndef TIM_STANDARD_ITEM_H
#define TIM_STANDARD_ITEM_H

#include <QStandardItem>
#include <libkawaii-fi/ies/traffic_indication_map.h>

class TimStandardItem : public QStandardItem {
public:
	TimStandardItem(const TrafficIndicationMap &tim);
};

#endif // TIM_STANDARD_ITEM_H
