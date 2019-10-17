#include "libkawaii-fi/ies/supported_rates.h"

#include "libkawaii-fi/ies/information_element.h"
#include "standard-items/supported_rates_standard_item.h"

#include <QByteArray>
#include <QString>
#include <QStringList>
#include <cstdint>

class QStandardItem;

namespace {
	const std::uint8_t supported_rate_mask = 0x7f; // 0111 1111
	const std::uint8_t basic_rate_mask = 0x80;     // 1000 0000
} // namespace

namespace KawaiiFi::Ies {
	SupportedRates::SupportedRates(const std::string_view &bytes, unsigned int ie_id)
	    : InformationElement(bytes, ie_id)
	{
	}

	QStandardItem *SupportedRates::standard_item() const
	{
		return new SupportedRatesStandardItem(*this);
	}

	QString SupportedRates::summary() const { return text_rates().join(", "); }

	QSet<double> SupportedRates::basic_rates() const
	{
		QSet<double> basic_rates;
		for (const auto &rate_byte : bytes()) {
			// The most significant bit of the rate byte indicates whether the rate is
			// basic/mandatory
			if ((static_cast<std::uint8_t>(rate_byte) & basic_rate_mask) != 0) {
				// The seven low-order bits are the rate as a multiple of 500 kbps
				// So divide by 2 to get the rate in mbps
				double rate_mbps =
				        (static_cast<std::uint8_t>(rate_byte) & supported_rate_mask) / 2.0;
				basic_rates.insert(rate_mbps);
			}
		}
		return basic_rates;
	}

	QSet<double> SupportedRates::rates() const
	{
		QSet<double> rates;
		for (const auto &rate_byte : bytes()) {
			// The seven low-order bits are the rate as a multiple of 500 kbps
			// So divide by 2 to get the rate in mbps
			double rate_mbps = (static_cast<std::uint8_t>(rate_byte) & supported_rate_mask) / 2.0;
			rates.insert(rate_mbps);
		}
		return rates;
	}

	QStringList SupportedRates::text_rates() const
	{
		QStringList rates;
		for (const auto &rate_byte : bytes()) {
			bool is_basic = (static_cast<std::uint8_t>(rate_byte) & basic_rate_mask) != 0;
			double rate_mbps = (static_cast<std::uint8_t>(rate_byte) & supported_rate_mask) / 2.0;
			rates.append(is_basic ? QString("%0*").arg(rate_mbps) : QString::number(rate_mbps));
		}
		return rates;
	}

	bool SupportedRates::is_extended_supported_rates() const
	{
		return id() == WLAN_EID_EXT_SUPP_RATES;
	}
} // namespace KawaiiFi::Ies
