#ifndef NL_WIFI_SCAN_H
#define NL_WIFI_SCAN_H

#include <QVector>
#include <libkawaii-fi/access_point.h>

namespace KawaiiFi {
	int trigger_scan_with_interface(unsigned int interface_index);

	int wait_for_new_wifi_scan_results(unsigned int timeout_seconds = 10);

	int get_wifi_scan_results(unsigned int interface_index, QVector<AccessPoint> &aps);
} // namespace KawaiiFi

#endif
