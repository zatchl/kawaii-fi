#include "supported_rates_standard_item.h"

#include "libkawaii-fi/ies/supported_rates.h"

#include <QString>
#include <QStringList>

SupportedRatesStandardItem::SupportedRatesStandardItem(const SupportedRates &supported_rates)
    : QStandardItem(supported_rates.is_extended_supported_rates() ? "Extended Supported Rates"
                                                                  : "Supported Rates")
{
	for (const auto &rate : supported_rates.text_rates()) {
		appendRow({new QStandardItem("Supported Rate"),
		           new QStandardItem(QString("%0 Mbit/sec").arg(rate))});
	}
}
