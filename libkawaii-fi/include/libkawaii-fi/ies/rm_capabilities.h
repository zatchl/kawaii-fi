#ifndef RM_CAPABILITIES_H
#define RM_CAPABILITIES_H

#include "information_element.h"

class RmCapabilities : public InformationElement {
public:
	RmCapabilities() = default;
	RmCapabilities(const InformationElement &ie);
};

inline const unsigned int WLAN_EID_RRM_ENABLED_CAPABILITIES = 70;

#endif // RM_CAPABILITIES_H
