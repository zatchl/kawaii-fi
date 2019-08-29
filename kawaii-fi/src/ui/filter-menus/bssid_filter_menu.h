#ifndef BSSID_FILTER_MENU_H
#define BSSID_FILTER_MENU_H

#include "access_point_filter_menu.h"

class QWidget;

class BssidFilterMenu : public AccessPointFilterMenu {
public:
	BssidFilterMenu(QWidget *parent = nullptr);
};

#endif // BSSID_FILTER_MENU_H
