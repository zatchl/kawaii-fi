#ifndef ERP_INFO_H
#define ERP_INFO_H

#include "information_element.h"

class ErpInfo : public InformationElement {
public:
	ErpInfo() = default;
	ErpInfo(const InformationElement &ie);

	[[nodiscard]] bool non_erp_present() const;
	[[nodiscard]] bool use_protection() const;
	[[nodiscard]] bool barker_preamble_mode() const;
};

inline const unsigned int WLAN_EID_ERP_INFO = 42;

#endif // ERP_INFO_H
