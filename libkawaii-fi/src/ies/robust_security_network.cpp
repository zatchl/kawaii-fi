#include "libkawaii-fi/ies/robust_security_network.h"

#include "libkawaii-fi/ies/information_element.h"

RobustSecurityNetwork::RobustSecurityNetwork(const InformationElement &ie)
    : InformationElement(ie.bytes())
{
}
