#include "libkawaii-fi/ies/ssid.h"

#include "libkawaii-fi/ies/information_element.h"

#include <QStandardItem>

Ssid::Ssid(const std::string_view &bytes) : InformationElement(bytes, WLAN_EID_SSID) {}

QStandardItem *Ssid::standard_item() const { return new QStandardItem("SSID"); }

QString Ssid::summary() const { return bytes(); }
