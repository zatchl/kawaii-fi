#ifndef SUPPORTED_RATES_STANDARD_ITEM_H
#define SUPPORTED_RATES_STANDARD_ITEM_H

#include <QStandardItem>

class SupportedRates;

class SupportedRatesStandardItem : public QStandardItem {
public:
	explicit SupportedRatesStandardItem(const SupportedRates &supported_rates);
};

#endif // SUPPORTED_RATES_STANDARD_ITEM_H
