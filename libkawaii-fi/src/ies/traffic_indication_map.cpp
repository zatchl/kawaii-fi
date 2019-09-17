#include "libkawaii-fi/ies/traffic_indication_map.h"

#include "libkawaii-fi/ies/information_element.h"
#include "standard-items/tim_standard_item.h"

#include <string_view>

class QStandardItem;

TrafficIndicationMap::TrafficIndicationMap(const std::string_view &bytes)
    : InformationElement(bytes, WLAN_EID_TIM)
{
}

QStandardItem *TrafficIndicationMap::standard_item() const { return new TimStandardItem(*this); }
