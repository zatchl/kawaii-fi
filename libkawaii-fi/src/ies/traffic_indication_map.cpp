#include "libkawaii-fi/ies/traffic_indication_map.h"

#include "libkawaii-fi/ies/information_element.h"

TrafficIndicationMap::TrafficIndicationMap(const InformationElement &ie)
    : InformationElement(ie.bytes())
{
}
