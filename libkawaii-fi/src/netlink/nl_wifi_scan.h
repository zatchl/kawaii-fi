#ifndef NL_WIFI_SCAN_H
#define NL_WIFI_SCAN_H

class AccessPoint;

template <class T>
class QVector;

bool update_aps_using_last_scan(QVector<AccessPoint> &aps, unsigned int if_index);

#endif // NL_WIFI_SCAN_H
