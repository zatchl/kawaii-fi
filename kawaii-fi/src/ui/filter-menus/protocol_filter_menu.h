#ifndef PROTOCOL_FILTER_MENU_H
#define PROTOCOL_FILTER_MENU_H

#include "access_point_filter_menu.h"

#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/standard.h>

class QWidget;

class ProtocolFilterMenu : public AccessPointFilterMenu {
public:
	ProtocolFilterMenu(QWidget *parent = nullptr);

	[[nodiscard]] KawaiiFi::Standards standards() const;
};

#endif // PROTOCOL_FILTER_MENU_H
