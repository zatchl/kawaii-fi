#ifndef DS_PARAMETER_H
#define DS_PARAMETER_H

#include "information_element.h"

class DsParameter : public InformationElement {
public:
	DsParameter() = default;
	DsParameter(const InformationElement &ie);

	[[nodiscard]] unsigned int channel() const;
};

inline const unsigned int WLAN_EID_DS_PARAMS = 3;

#endif // DS_PARAMETER_H
