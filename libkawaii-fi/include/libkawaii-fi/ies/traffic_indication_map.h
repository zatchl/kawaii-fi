#ifndef TRAFFIC_INDICATION_MAP_H
#define TRAFFIC_INDICATION_MAP_H

#include "information_element.h"
#include "string_view"

class QStandardItem;

namespace KawaiiFi::Ies {
	class TrafficIndicationMap : public InformationElement {
	public:
		TrafficIndicationMap() = default;
		explicit TrafficIndicationMap(const std::string_view &bytes);

		[[nodiscard]] QStandardItem *standard_item() const override;
	};

	inline const unsigned int WLAN_EID_TIM = 5;
} // namespace KawaiiFi::Ies

#endif // TRAFFIC_INDICATION_MAP_H
