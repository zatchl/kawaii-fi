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

	// Adjust the margins between widgets and the edges of the window
	const int window_content_margin = 5;
	setContentsMargins(window_content_margin, window_content_margin, window_content_margin,
	                   window_content_margin);
	// Make the width of separators (which is the distance between the central widget and dock
	// widgets) the same as the margin between widgets and the edges of the window
	setStyleSheet("QMainWindow::separator { width: 5px; height: 5px; }");
}

MainWindow::~MainWindow() { delete ui_; }
