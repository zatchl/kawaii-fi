#ifndef NL_WIFI_SCAN_H
#define NL_WIFI_SCAN_H

struct AccessPoint;

template <class Key, class T>
class QHash;

class QString;

namespace KawaiiFi {
	int trigger_scan_with_interface(unsigned int interface_index);

	int wait_for_new_wifi_scan_results(unsigned int timeout_seconds = 10);

	int get_wifi_scan_results(unsigned int interface_index, QHash<QString, AccessPoint> &aps);
} // namespace KawaiiFi

#endif
