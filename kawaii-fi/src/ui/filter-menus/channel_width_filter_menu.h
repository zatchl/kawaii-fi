#ifndef CHANNEL_WIDTH_FILTER_MENU_H
#define CHANNEL_WIDTH_FILTER_MENU_H

#include "access_point_filter_menu.h"

#include <QSet>

class QWidget;

class ChannelWidthFilterMenu : public AccessPointFilterMenu {
public:
	ChannelWidthFilterMenu(QWidget *parent = nullptr);

	[[nodiscard]] QSet<unsigned int> channel_widths() const;

private:
	//	QHash<unsigned int, FilterMenuCheckBox *> channel_width_check_boxes_;
};

#endif // CHANNEL_WIDTH_FILTER_MENU_H
