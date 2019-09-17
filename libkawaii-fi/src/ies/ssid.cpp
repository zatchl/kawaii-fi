#include "libkawaii-fi/ies/ssid.h"

#include "libkawaii-fi/ies/information_element.h"

Ssid::Ssid(const InformationElement &ie) : InformationElement(ie.bytes()) {}
#include <QStandardItem>

QStandardItem *Ssid::standard_item() const { return new QStandardItem("SSID"); }

QString Ssid::summary() const { return bytes(); }
