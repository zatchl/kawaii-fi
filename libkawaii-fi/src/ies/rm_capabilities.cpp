#include "libkawaii-fi/ies/rm_capabilities.h"

#include "libkawaii-fi/ies/information_element.h"

RmCapabilities::RmCapabilities(const InformationElement &ie) : InformationElement(ie.bytes()) {}
