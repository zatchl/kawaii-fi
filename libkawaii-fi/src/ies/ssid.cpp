#include "libkawaii-fi/ies/ssid.h"

#include "libkawaii-fi/ies/information_element.h"

Ssid::Ssid(const InformationElement &ie) : InformationElement(ie.bytes()) {}
