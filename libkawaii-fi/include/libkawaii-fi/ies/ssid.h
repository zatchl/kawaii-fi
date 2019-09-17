#ifndef SSID_H
#define SSID_H

#include "information_element.h"


class QStandardItem;

class Ssid : public InformationElement {
public:
	Ssid() = default;
	Ssid(const InformationElement &ie);

	[[nodiscard]] QStandardItem *standard_item() const override;
	[[nodiscard]] QString summary() const override;
};

inline const unsigned int WLAN_EID_SSID = 0;

#endif // SSID_H
