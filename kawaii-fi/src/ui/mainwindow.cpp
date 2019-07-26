#include "mainwindow.h"

#include "kawaiifi_server_interface.h"
#include "models/access_point_table_model.h"
#include "ui/access_point_chart.h"
#include "ui_mainwindow.h"

#include <QAbstractButton>
#include <QAbstractItemView>
#include <QChartView>
#include <QDBusMetaType>
#include <QDBusPendingReply>
#include <QHeaderView>
#include <QMap>
#include <QSizePolicy>
#include <QStatusBar>
#include <QStringList>
#include <QStyle>
#include <QTableView>
#include <QToolBar>
#include <QVector>
#include <QWidget>
#include <QtGlobal>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/information_element.h>

namespace {
	const QMap<QString, int> scan_interval_map = {{QT_TR_NOOP("10 seconds"), 10},
	                                              {QT_TR_NOOP("30 seconds"), 30},
	                                              {QT_TR_NOOP("60 seconds"), 60}};

	const int window_content_margin = 5;
	const int toolbar_bottom_margin = 5;
	const int toolbar_widget_spacing = 5;
	const int status_message_timeout_ms = 2000;

	void add_spacer(QToolBar *toolbar, int spacer_width = toolbar_widget_spacing)
	{
		QWidget *spacer = new QWidget(toolbar);
		spacer->setFixedWidth(spacer_width);
		toolbar->addWidget(spacer);
	}
} // namespace

using namespace KawaiiFi;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui_(new Ui::MainWindow)
{
	ui_->setupUi(this);

	// Adjust the margins between widgets and the edges of the window
	setContentsMargins(window_content_margin, window_content_margin, window_content_margin,
	                   window_content_margin);
	// Make the width of separators (which is the distance between the central widget and dock
	// widgets) the same as the margin between widgets and the edges of the window
	setStyleSheet("QMainWindow::separator { width: 5px; height: 5px; }");

	create_toolbar();
	create_charts();
	create_table();

	set_up_server_interface();
	refresh_wireless_nics();
	scan();
	connect(scan_timer_, &QTimer::timeout, this, &MainWindow::scan);
	start_scan_timer(current_scan_interval());
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::create_toolbar()
{
	scan_pause_resume_button_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	scan_pause_resume_button_->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
	connect(scan_pause_resume_button_, &QPushButton::clicked, [=]() {
		scanning_enabled_ = !scanning_enabled_;
		if (scanning_enabled_) {
			start_scan_timer(current_scan_interval());
			scan_pause_resume_button_->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
		} else {
			stop_scan_timer();
			scan_pause_resume_button_->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
		}
	});

	scan_interval_combo_box_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	scan_interval_combo_box_->addItems(scan_interval_map.keys());
	connect(scan_interval_combo_box_, &QComboBox::currentTextChanged, [=]() {
		if (scanning_enabled_) {
			start_scan_timer(current_scan_interval());
		}
	});

	ap_filter_line_edit_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	ap_filter_line_edit_->setPlaceholderText(tr("Add filter..."));

	wireless_interface_combo_box_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	QToolBar *toolbar = addToolBar("");
	toolbar->setMovable(false);
	toolbar->setContentsMargins(0, 0, 0, toolbar_bottom_margin);
	toolbar->addWidget(scan_pause_resume_button_);
	add_spacer(toolbar);
	toolbar->addWidget(scan_interval_combo_box_);
	add_spacer(toolbar);
	toolbar->addWidget(ap_filter_line_edit_);
	add_spacer(toolbar);
	toolbar->addWidget(wireless_interface_combo_box_);
}

void MainWindow::create_charts()
{
	two_point_four_ghz_chart_->set_model(ap_proxy_model_);
	ui_->two_four_ghz_chart_view->setChart(two_point_four_ghz_chart_);
	five_ghz_chart_->set_model(ap_proxy_model_);
	ui_->five_ghz_chart_view->setChart(five_ghz_chart_);
}

void MainWindow::create_table()
{
	ap_proxy_model_->setSourceModel(ap_table_model_);
	ui_->apTableView->setModel(ap_proxy_model_);
	ui_->apTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui_->apTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::set_up_server_interface()
{
	// Register the AccessPoint type with the Qt D-Bus Type System and the Qt meta-type system
	qDBusRegisterMetaType<AccessPoint>();
	qDBusRegisterMetaType<QVector<AccessPoint>>();
	qDBusRegisterMetaType<InformationElement>();

	// When a Wi-Fi scan has completed, the server emits a signal
	// Connect that signal to the handle_scan_completed function
	connect(server_interface_, &org::kawaiifi::Server::wifi_scan_completed, this,
	        &MainWindow::handle_scan_completed);
}

void MainWindow::scan()
{
	ui_->statusBar->showMessage("Starting new scan", status_message_timeout_ms);
	server_interface_->trigger_wifi_scan(wireless_interface_combo_box_->currentText());
}

void MainWindow::handle_scan_completed(const QString &nic_name)
{
	if (!scanning_enabled_ || nic_name != wireless_interface_combo_box_->currentText()) {
		return;
	}

	QVector<AccessPoint> aps = server_interface_->access_points(nic_name).value();
	ap_table_model_->update_access_points(aps);
}

void MainWindow::refresh_wireless_nics()
{
	// Set wireless nics
	wireless_interface_combo_box_->clear();
	QStringList nic_names = server_interface_->wireless_nic_names().value();
	for (const QString &nic_name : nic_names) {
		wireless_interface_combo_box_->addItem(nic_name);
	}
	wireless_interface_combo_box_->setCurrentIndex(0);
}

int MainWindow::current_scan_interval()
{
	return scan_interval_map[scan_interval_combo_box_->currentText()];
}

void MainWindow::start_scan_timer(int interval_sec)
{
	if (interval_sec > 0) {
		scan_timer_->start(interval_sec * 1000);
	}
}

void MainWindow::stop_scan_timer() { scan_timer_->stop(); }
