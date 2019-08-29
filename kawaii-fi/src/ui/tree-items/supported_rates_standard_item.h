#ifndef SUPPORTED_RATES_STANDARD_ITEM_H
#define SUPPORTED_RATES_STANDARD_ITEM_H

#include "libkawaii-fi/ies/supported_rates.h"

#include <QStandardItem>

class SupportedRatesStandardItem : public QStandardItem {
public:
	SupportedRatesStandardItem(const SupportedRates &supported_rates, bool extended_rates = false);
};

#endif // SUPPORTED_RATES_STANDARD_ITEM_H
