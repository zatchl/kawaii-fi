#include "channel_filter_menu.h"

#include "ui/filter-menus/access_point_filter_menu.h"

#include <QSet>
#include <QString>
#include <QVariant>
#include <QVector>

class QMenu;
class QWidget;

ChannelFilterMenu::ChannelFilterMenu(QWidget *parent) : AccessPointFilterMenu("Channel", parent)
{
	QMenu *two_point_four_menu = addMenu("2.4 GHz");
	constexpr unsigned int min_two_point_four_channel = 1;
	constexpr unsigned int max_two_point_four_channel = 14;
	for (unsigned int i = min_two_point_four_channel; i <= max_two_point_four_channel; ++i) {
		add_filter_check_box(two_point_four_menu, QString::number(i), i);
	}

	QMenu *unii_1_menu = addMenu("5 GHz U-NII-1");
	constexpr unsigned int min_unii_1_channel = 32;
	constexpr unsigned int max_unii_1_channel = 48;
	for (unsigned int i = min_unii_1_channel; i <= max_unii_1_channel; i += 2) {
		add_filter_check_box(unii_1_menu, QString::number(i), i);
	}

	QMenu *unii_2a_menu = addMenu("5 GHz U-NII-2A");
	constexpr unsigned int min_unii_2a_channel = 50;
	constexpr unsigned int max_unii_2a_channel = 68;
	const QSet<unsigned int> unii_2a_invalid_channels = {66};
	for (unsigned int i = min_unii_2a_channel; i <= max_unii_2a_channel; i += 2) {
		if (unii_2a_invalid_channels.contains(i)) {
			continue;
		}
		add_filter_check_box(unii_2a_menu, QString::number(i), i);
	}

	QMenu *unii_2c_menu = addMenu("5 GHz U-NII-2C");
	constexpr unsigned int min_unii_2c_channel = 96;
	constexpr unsigned int max_unii_2c_channel = 144;
	const QSet<unsigned int> unii_2c_invalid_channels = {98, 130};
	for (unsigned int i = min_unii_2c_channel; i <= max_unii_2c_channel; i += 2) {
		if (unii_2c_invalid_channels.contains(i)) {
			continue;
		}
		add_filter_check_box(unii_2c_menu, QString::number(i), i);
	}

	QMenu *unii_3_menu = addMenu("5 GHz U-NII-3");
	constexpr unsigned int min_unii_3_channel = 149;
	constexpr unsigned int max_unii_3_channel = 173;
	const QSet<unsigned int> unii_3_invalid_channels = {163, 167, 171};
	for (unsigned int i = min_unii_3_channel; i <= max_unii_3_channel; i += 2) {
		if (unii_3_invalid_channels.contains(i)) {
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
