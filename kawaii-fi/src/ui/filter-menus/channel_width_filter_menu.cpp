#include "channel_width_filter_menu.h"

#include "ui/filter-menus/access_point_filter_menu.h"

#include <QString>
#include <QVariant>
#include <QVector>
#include <initializer_list>

class QWidget;

ChannelWidthFilterMenu::ChannelWidthFilterMenu(QWidget *parent)
    : AccessPointFilterMenu("Channel Width", parent)
{
	for (unsigned int channel_width : {20U, 40U, 80U, 160U}) {
		add_filter_check_box(QString("%0 MHz").arg(channel_width), channel_width);
	}
}

QSet<unsigned int> ChannelWidthFilterMenu::channel_widths() const
{
	QSet<unsigned int> channel_widths;
	for (const auto check_box : checked_filter_check_boxes()) {
		channel_widths.insert(check_box->data().toUInt());
	}
	return channel_widths;
}
