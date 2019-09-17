#ifndef NL_PARSE_ATTR_H
#define NL_PARSE_ATTR_H

#include "libkawaii-fi/capabilities.h"
#include "libkawaii-fi/connection_status.h"
#include "libkawaii-fi/ies/ie_variant.h"

#include <QString>
#include <QVector>

struct nlattr;

[[nodiscard]] QString parse_bssid(nlattr *attr);
[[nodiscard]] int parse_signal_strength_mbm(nlattr *attr);
[[nodiscard]] unsigned int parse_age_ms(nlattr *attr);
[[nodiscard]] ConnectionStatus parse_connection_status(nlattr *attr);
[[nodiscard]] unsigned int parse_frequency(nlattr *attr);
[[nodiscard]] Capabilities parse_capabilities(nlattr *attr);
[[nodiscard]] unsigned int parse_tsf(nlattr *attr);
[[nodiscard]] unsigned int parse_beacon_interval(nlattr *attr);
[[nodiscard]] QVector<IeVariant> parse_ies(nlattr *attr);

#endif // NL_PARSE_ATTR_H
