#include "channel_filter_menu.h"

#include "ui/filter-menus/access_point_filter_menu.h"

#include <QString>
#include <QVariant>
#include <QVector>

class QMenu;
class QWidget;

ChannelFilterMenu::ChannelFilterMenu(QWidget *parent) : AccessPointFilterMenu("Channel", parent)
{
	QMenu *two_point_four_menu = addMenu("2.4 GHz");
	for (unsigned int i = 1; i <= 14; ++i) {
		add_filter_check_box(two_point_four_menu, QString::number(i), i);
	}

	QMenu *unii_1_menu = addMenu("5 GHz U-NII-1");
	for (unsigned int i = 32; i <= 48; i += 2) {
		add_filter_check_box(unii_1_menu, QString::number(i), i);
	}

	QMenu *unii_2a_menu = addMenu("5 GHz U-NII-2A");
	for (unsigned int i = 50; i <= 68; i += 2) {
		if (i == 66) {
			continue;
		}
		add_filter_check_box(unii_2a_menu, QString::number(i), i);
	}

	QMenu *unii_2c_menu = addMenu("5 GHz U-NII-2C");
	for (unsigned int i = 96; i <= 144; i += 2) {
		if ((i == 98) || (i == 130)) {
			continue;
		}
		add_filter_check_box(unii_2c_menu, QString::number(i), i);
	}

	QMenu *unii_3_menu = addMenu("5 GHz U-NII-3");
	for (unsigned int i = 149; i <= 173; i += 2) {
		if ((i == 163) || (i == 167) || (i == 171)) {
			continue;
		}
		add_filter_check_box(unii_3_menu, QString::number(i), i);
	}
}

QSet<unsigned int> ChannelFilterMenu::channels() const
{
	QSet<unsigned int> channels;
	for (const auto check_box : checked_filter_check_boxes()) {
		channels.insert(check_box->data().toUInt());
	}
	return channels;
}
