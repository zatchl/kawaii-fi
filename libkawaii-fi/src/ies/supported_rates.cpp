#include "libkawaii-fi/ies/supported_rates.h"

#include "libkawaii-fi/ies/information_element.h"

#include <QByteArray>
#include <cstdint>

namespace {
	const std::uint8_t supported_rate_mask = 0x7f; // 0111 1111
	const std::uint8_t basic_rate_mask = 0x80;     // 1000 0000
} // namespace

SupportedRates::SupportedRates(const InformationElement &ie) : InformationElement(ie) {}

QSet<double> SupportedRates::basic_rates() const
{
	QSet<double> basic_rates;
	for (const auto &rate_byte : bytes()) {
		// The most significant bit of the rate byte indicates whether the rate is
		// basic/mandatory
		if (rate_byte & basic_rate_mask) {
			// The seven low-order bits are the rate as a multiple of 500 kbps
			// So divide by 2 to get the rate in mbps
			double rate_mbps = static_cast<double>(rate_byte & supported_rate_mask) / 2;
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
		double rate_mbps = static_cast<double>(rate_byte & supported_rate_mask) / 2;
		rates.insert(rate_mbps);
	}
	return rates;
}
