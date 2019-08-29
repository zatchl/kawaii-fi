#ifndef SSID_FILTER_MENU_H
#define SSID_FILTER_MENU_H

#include "access_point_filter_menu.h"

class QWidget;

class SsidFilterMenu : public AccessPointFilterMenu {
public:
	SsidFilterMenu(QWidget *parent = nullptr);
};

#endif // SSID_FILTER_MENU_H
