#ifndef TRAFFIC_INDICATION_MAP_H
#define TRAFFIC_INDICATION_MAP_H

#include "information_element.h"

class TrafficIndicationMap : public InformationElement {
public:
	TrafficIndicationMap() = default;
	TrafficIndicationMap(const InformationElement &ie);
};

inline const unsigned int WLAN_EID_TIM = 5;

#endif // TRAFFIC_INDICATION_MAP_H
