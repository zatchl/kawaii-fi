#ifndef PROTOCOL_FILTER_MENU_H
#define PROTOCOL_FILTER_MENU_H

#include "access_point_filter_menu.h"

#include <QSet>
#include <libkawaii-fi/access_point.h>

class QWidget;

class ProtocolFilterMenu : public AccessPointFilterMenu {
public:
	ProtocolFilterMenu(QWidget *parent = nullptr);

	[[nodiscard]] QSet<Protocol> protocols() const;
};

#endif // PROTOCOL_FILTER_MENU_H
