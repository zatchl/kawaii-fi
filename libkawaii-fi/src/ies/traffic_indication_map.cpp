#include "libkawaii-fi/ies/traffic_indication_map.h"

#include "libkawaii-fi/ies/information_element.h"
#include "standard-items/tim_standard_item.h"

TrafficIndicationMap::TrafficIndicationMap(const InformationElement &ie)
    : InformationElement(ie.bytes())

class QStandardItem;

{
}

QStandardItem *TrafficIndicationMap::standard_item() const { return new TimStandardItem(*this); }
