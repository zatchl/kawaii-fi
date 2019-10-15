#ifndef NL_WIFI_SCAN_H
#define NL_WIFI_SCAN_H

#include "libkawaii-fi/access_point.h"

template <class T>
class QVector;

namespace KawaiiFi {
	bool update_aps_using_last_scan(QVector<KawaiiFi::AccessPoint> &aps, unsigned int if_index);
} // namespace KawaiiFi

#endif // NL_WIFI_SCAN_H
