#ifndef CHANNEL_FILTER_MENU_H
#define CHANNEL_FILTER_MENU_H

#include "access_point_filter_menu.h"

#include <QSet>

class QWidget;

class ChannelFilterMenu : public AccessPointFilterMenu {
public:
	ChannelFilterMenu(QWidget *parent = nullptr);

	[[nodiscard]] QSet<unsigned int> channels() const;
};

#endif // CHANNEL_FILTER_MENU_H
