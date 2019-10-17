#include "libkawaii-fi/standard.h"

#include "libkawaii-fi/channel.h"
#include "libkawaii-fi/ies/ht_capabilities.h"
#include "libkawaii-fi/ies/information_element.h"
#include "libkawaii-fi/ies/supported_rates.h"
#include "libkawaii-fi/ies/variant.h"
#include "libkawaii-fi/ies/vht_capabilities.h"

#include <QSet>
#include <QString>
#include <QStringList>
#include <QVector>
#include <algorithm>
#include <variant>

namespace KawaiiFi {
	QString standard_to_string(Standard standard)
	{
		switch (standard) {
		case Standard::B:
			return "b";
		case Standard::G:
			return "g";
		case Standard::N:
			return "n";
		case Standard::A:
			return "a";
		case Standard::AC:
			return "ac";
		case Standard::AX:
			return "ax";
		}

		return "";
	}

	QString standards_to_string(Standards standards, const QString &delimeter)
	{
		QStringList standard_strings;
		const auto all_standards = {Standard::B, Standard::G,  Standard::N,
		                            Standard::A, Standard::AC, Standard::AX};
		for (Standard standard : all_standards) {
			if (standards.testFlag(standard)) {
				standard_strings.append(standard_to_string(standard));
			}
		}

		return standard_strings.join(delimeter);
	}

	Standards standards_from_ies(const QVector<Ies::Variant> &ies, Channel::Band band)
	{
		Standards standards;

		QSet<double> supported_rates;
		bool ht_capability_ie_exists = false;
		bool vht_capability_ie_exists = false;
		for (const auto &ie : ies) {
			if (auto supported_rates_ie = std::get_if<Ies::SupportedRates>(&ie)) {
				supported_rates.unite(supported_rates_ie->rates());
				continue;
			}
			if (!ht_capability_ie_exists) {
				ht_capability_ie_exists = (std::get_if<Ies::HtCapabilities>(&ie) != nullptr);
			}
			if (!vht_capability_ie_exists) {
				vht_capability_ie_exists = (std::get_if<Ies::VhtCapabilities>(&ie) != nullptr);
			}
		}

		switch (band) {
		case Channel::Band::TwoPointFourGhz: {
			// 802.11b and 802.11g are 2.4 GHz only
			const auto b_rates = {1.0, 2.0, 5.5, 11.0};
			const bool contains_any_b_rate =
			        std::any_of(b_rates.begin(), b_rates.end(), [&supported_rates](double rate) {
				        return supported_rates.contains(rate);
			        });
			if (contains_any_b_rate) {
				standards.setFlag(Standard::B);
			}

			const auto g_rates = {6.0, 9.0, 12.0, 18.0, 24.0, 36.0, 48.0, 54.0};
			const bool contains_any_g_rate =
			        std::any_of(g_rates.begin(), g_rates.end(), [&supported_rates](double rate) {
				        return supported_rates.contains(rate);
			        });
			if (contains_any_g_rate) {
				standards.setFlag(Standard::G);
			}

			break;
		}
		case Channel::Band::FiveGhz:
			// 802.11a and 802.11ac are 5 GHz only
			standards.setFlag(Standard::A);

			if (vht_capability_ie_exists) {
				standards.setFlag(Standard::AC);
			}

			break;
		default:
			break;
		}

		// 802.11n applies to both 2.4 and 5 GHz
		if (ht_capability_ie_exists) {
			standards.setFlag(Standard::N);
		}

		return standards;
	}
} // namespace KawaiiFi
