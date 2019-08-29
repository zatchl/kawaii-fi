#ifndef COUNTRY_INFO_STANDARD_ITEM_H
#define COUNTRY_INFO_STANDARD_ITEM_H

#include <QStandardItem>
#include <libkawaii-fi/channel.h>
#include <libkawaii-fi/ies/country_info.h>

class CountryInfoStandardItem : public QStandardItem {
public:
	CountryInfoStandardItem(const CountryInfo &country_info, WifiBand wifi_band);
};

#endif // COUNTRY_INFO_STANDARD_ITEM_H
