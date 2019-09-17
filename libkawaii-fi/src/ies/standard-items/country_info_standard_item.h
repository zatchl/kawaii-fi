#ifndef COUNTRY_INFO_STANDARD_ITEM_H
#define COUNTRY_INFO_STANDARD_ITEM_H

#include <QStandardItem>

class CountryInfo;

class CountryInfoStandardItem : public QStandardItem {
public:
	explicit CountryInfoStandardItem(const CountryInfo &country_info);
};

#endif // COUNTRY_INFO_STANDARD_ITEM_H
