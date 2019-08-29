#include "ssid_filter_menu.h"

#include "ui/filter-menus/access_point_filter_menu.h"

#include <QAction>

class QWidget;

SsidFilterMenu::SsidFilterMenu(QWidget *parent) : AccessPointFilterMenu("SSID", parent)
{
	QAction *test_ssid_action = new QAction("HOMEFE12", this);
	test_ssid_action->setCheckable(true);
	addAction(test_ssid_action);

	QAction *test_ssid_action_2 = new QAction("LEDE", this);
	test_ssid_action_2->setCheckable(true);
	addAction(test_ssid_action_2);

	QAction *test_ssid_action_3 = new QAction("nan2", this);
	test_ssid_action_3->setCheckable(true);
	addAction(test_ssid_action_3);
}
