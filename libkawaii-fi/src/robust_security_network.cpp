#include "libkawaii-fi/robust_security_network.h"

#include "libkawaii-fi/information_element.h"

RobustSecurityNetwork::RobustSecurityNetwork(const InformationElement &ie)
    : InformationElement(ie.bytes())
{
}
