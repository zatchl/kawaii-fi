#include "tim_standard_item.h"

#include <libkawaii-fi/ies/traffic_indication_map.h>

TimStandardItem::TimStandardItem(const TrafficIndicationMap &tim) : QStandardItem("TIM") {}
