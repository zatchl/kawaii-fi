#include "mainwindow.h"

#include "access_point_table.h"
#include "ui/access_point_chart.h"
#include "ui/access_point_detail_tree.h"
#include "ui/access_point_status_bar.h"
#include "ui/filter-menus/bssid_filter_menu.h"
#include "ui/filter-menus/channel_filter_menu.h"
#include "ui/filter-menus/channel_width_filter_menu.h"
#include "ui/filter-menus/protocol_filter_menu.h"
#include "ui/filter-menus/ssid_filter_menu.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QActionGroup>
#include <QChartView>
#include <QList>
#include <QMenu>
#include <QSplitter>
#include <QStringList>
#include <QTabWidget>
#include <climits>
#include <libkawaii-fi/channel.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui_(new Ui::MainWindow)
{
	ui_->setupUi(this);

	// Set the top and bottom views (QTableView and QTabWidget) to the same height
	ui_->splitter->setSizes({INT_MAX, INT_MAX});

	// Place a status bar in the corner of the tab widget
	auto status_bar_ = new AccessPointStatusBar(ui_->pause_action, ui_->resume_action, this);
	ui_->tabWidget->setCornerWidget(status_bar_);

	// Create an AccessPointChart for 2.4 GHz and 5 GHz access points
	ui_->two_four_ghz_chart_view->setChart(
	        new AccessPointChart(*scanner_, KawaiiFi::Channel::Band::TwoPointFourGhz));
	ui_->five_ghz_chart_view->setChart(
	        new AccessPointChart(*scanner_, KawaiiFi::Channel::Band::FiveGhz));

	// Pass the AccessPointScanner object to the access point table view and IE tree view
	ui_->ap_table_view->set_ap_scanner(*scanner_);
	ui_->ie_tree_view->set_ap_scanner(scanner_);

	// Show the information elements of the access point selected in the table
	connect(ui_->ap_table_view, &AccessPointTableView::access_point_selected, ui_->ie_tree_view,
	        &AccessPointDetailTreeView::show_ies);

	// Pause or resume scanning when the pause or resume actions are triggered
	connect(ui_->pause_action, &QAction::triggered, this, &MainWindow::pause_scanning);
	connect(ui_->resume_action, &QAction::triggered, this, &MainWindow::resume_scanning);

	// Trigger the next scan after receiving the results of the last one
	connect(scanner_, &KawaiiFi::Scanning::AccessPointScanner::access_points_changed, this,
	        &MainWindow::resume_scanning);

	setWindowTitle("Kawaii-Fi");

	populate_menu_bar();

	// Trigger the first scan
	resume_scanning();
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::populate_menu_bar()
{
	// Use the filter menus from the table view for the filter menu in the menu bar
	ui_->filter_menu->addMenu(ui_->ap_table_view->ssid_filter_menu());
	ui_->filter_menu->addMenu(ui_->ap_table_view->bssid_filter_menu());
	ui_->filter_menu->addMenu(ui_->ap_table_view->channel_filter_menu());
	ui_->filter_menu->addMenu(ui_->ap_table_view->channel_width_filter_menu());
	ui_->filter_menu->addMenu(ui_->ap_table_view->protocol_filter_menu());

	// Place all the interface actions in a group so only one can be selected at a time
	auto interface_group = new QActionGroup(this);
	const auto wifi_device_names = scanner_->wifi_device_names();
	for (const auto &nic_name : wifi_device_names) {
		auto nic_action = ui_->interface_menu->addAction(nic_name);
		nic_action->setActionGroup(interface_group);
		nic_action->setCheckable(true);
		connect(nic_action, &QAction::triggered, this, &MainWindow::resume_scanning);
	}

	// Select the first wireless interface
	if (!ui_->interface_menu->actions().isEmpty()) {
		ui_->interface_menu->actions().constFirst()->setChecked(true);
	}
}

void MainWindow::pause_scanning()
{
	scanner_->set_is_scanning(false);
	ui_->pause_action->setEnabled(false);
	ui_->resume_action->setEnabled(true);
}

void MainWindow::resume_scanning()
{
	scanner_->set_is_scanning(true);
	scanner_->scan(selected_wireless_interface());
	ui_->resume_action->setEnabled(false);
	ui_->pause_action->setEnabled(true);
}

QString MainWindow::selected_wireless_interface() const
{
	for (const auto action : ui_->interface_menu->actions()) {
		if (action->isChecked()) {
			return action->text();
		}
	}
	return "";
}
