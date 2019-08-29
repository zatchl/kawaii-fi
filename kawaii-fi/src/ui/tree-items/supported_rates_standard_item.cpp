#include "supported_rates_standard_item.h"

#include <QString>
#include <QStringList>

SupportedRatesStandardItem::SupportedRatesStandardItem(const SupportedRates &supported_rates,
                                                       bool extended_rates)
    : QStandardItem(extended_rates ? "Extended Supported Rates" : "Supported Rates")
{
	for (const auto &rate : supported_rates.text_rates()) {
		appendRow(new QStandardItem(QString("%0 Mbit/sec").arg(rate)));
	}
}
