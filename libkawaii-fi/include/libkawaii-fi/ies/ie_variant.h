#ifndef IE_VARIANT_H
#define IE_VARIANT_H

#include "country_info.h"
#include "ds_parameter.h"
#include "erp_info.h"
#include "extended_capabilities.h"
#include "ht_capabilities.h"
#include "ht_operations.h"
#include "information_element.h"
#include "power_constraint.h"
#include "rm_capabilities.h"
#include "robust_security_network.h"
#include "ssid.h"
#include "supported_rates.h"
#include "traffic_indication_map.h"
#include "vendor_specific.h"
#include "vht_capabilities.h"
#include "vht_operations.h"
#include "wpa.h"

#include <variant>

using IeVariant =
        std::variant<CountryInfo, DsParameter, ErpInfo, ExtendedCapabilities, HtCapabilities,
                     HtOperations, InformationElement, PowerConstraint, RmCapabilities,
                     RobustSecurityNetwork, Ssid, SupportedRates, TrafficIndicationMap,
                     VendorSpecific, VhtCapabilities, VhtOperations, Wpa>;

#endif // IE_VARIANT_H
