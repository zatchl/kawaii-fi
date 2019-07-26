#include "libkawaii-fi/ssid.h"

#include "libkawaii-fi/information_element.h"

Ssid::Ssid(const InformationElement &ie) : InformationElement(ie.bytes()) {}
