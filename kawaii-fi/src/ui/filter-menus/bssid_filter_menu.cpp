#include "bssid_filter_menu.h"

#include "ui/filter-menus/access_point_filter_menu.h"

class QWidget;

BssidFilterMenu::BssidFilterMenu(QWidget *parent) : AccessPointFilterMenu("BSSID", parent) {}
