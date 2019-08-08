#include "mainwindow.h"

#include "access_point_table.h"
#include "ui/access_point_chart.h"
#include "ui_mainwindow.h"

#include <QChartView>
#include <QStatusBar>
#include <libkawaii-fi/channel.h>
#include <libkawaii-fi/kawaiifi.h>

using namespace KawaiiFi;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui_(new Ui::MainWindow)
{
	ui_->setupUi(this);

	// Set the AccessPointTableView as the central widget
	setCentralWidget(table_view_);
	// Handle when an access point is selected in the table
	connect(table_view_, &AccessPointTableView::access_point_selected,
	        [this](const QString &bssid) { statusBar()->showMessage(bssid); });

	// Create an AccessPointChart for 2.4 GHz and 5 GHz access points
	ui_->two_four_ghz_chart_view->setChart(
	        new AccessPointChart(*scanner_, WifiBand::TwoPointFourGhz));
	ui_->five_ghz_chart_view->setChart(new AccessPointChart(*scanner_, WifiBand::FiveGhz));

	// Provide the toolbar with the names of any wireless nics
	toolbar_->set_wireless_nics(scanner_->wireless_nic_names());
	// Start/stop the scan timer when the toolbar's resume/pause button is clicked
	connect(toolbar_, &MainWindowToolbar::scanning_resumed,
	        [this](int scan_interval) { scan_timer_->start(scan_interval * 1000); });
	connect(toolbar_, &MainWindowToolbar::scanning_paused, [this]() { scan_timer_->stop(); });
	// Add the toolbar to this window
	addToolBar(toolbar_);

	// Adjust the margins between widgets and the edges of the window
	const int window_content_margin = 5;
	setContentsMargins(window_content_margin, window_content_margin, window_content_margin,
	                   window_content_margin);
	// Make the width of separators (which is the distance between the central widget and dock
	// widgets) the same as the margin between widgets and the edges of the window
	setStyleSheet("QMainWindow::separator { width: 5px; height: 5px; }");

	// Scan for new/updated access points when the scan timer times out
	connect(scan_timer_, &QTimer::timeout,
	        [this]() { scanner_->scan(toolbar_->current_wireless_nic()); });
	// Manually trigger the first scan
	scanner_->scan(toolbar_->current_wireless_nic());
	// Start the scan timer
	scan_timer_->start(toolbar_->current_scan_interval() * 1000);
}

MainWindow::~MainWindow() { delete ui_; }
