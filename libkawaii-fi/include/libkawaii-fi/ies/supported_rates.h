#ifndef SUPPORTED_RATES_H
#define SUPPORTED_RATES_H

#include "information_element.h"

#include <QSet>
#include <QString>
#include <QStringList>
#include <string_view>

class QStandardItem;

class SupportedRates : public InformationElement {
public:
	SupportedRates() = default;
	SupportedRates(const std::string_view &bytes, unsigned int ie_id_);

	[[nodiscard]] QStandardItem *standard_item() const override;
	[[nodiscard]] QString summary() const override;

	[[nodiscard]] QSet<double> basic_rates() const;
	[[nodiscard]] QSet<double> rates() const;
	[[nodiscard]] QStringList text_rates() const;
};

inline const unsigned int WLAN_EID_SUPP_RATES = 1;
inline const unsigned int WLAN_EID_EXT_SUPP_RATES = 50;

#endif // SUPPORTED_RATES_H
