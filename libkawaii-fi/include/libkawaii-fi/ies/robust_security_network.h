#ifndef ROBUST_SECURITY_NETWORK_H
#define ROBUST_SECURITY_NETWORK_H

#include "information_element.h"

class RobustSecurityNetwork : public InformationElement {
public:
	RobustSecurityNetwork() = default;
	RobustSecurityNetwork(const InformationElement &ie);

	[[nodiscard]] unsigned int version() const;
};

inline const unsigned int WLAN_EID_RSN = 48;

#endif // ROBUST_SECURITY_NETWORK_H
