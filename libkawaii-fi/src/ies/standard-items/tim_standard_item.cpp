#include "tim_standard_item.h"

class TrafficIndicationMap;

namespace KawaiiFi::Ies {
	TimStandardItem::TimStandardItem(const TrafficIndicationMap &tim) : QStandardItem("TIM") {}
} // namespace KawaiiFi::Ies
