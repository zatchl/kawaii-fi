#include "mainwindow.h"

#include "kawaiifi_server_interface.h"
#include "models/access_point_table_model.h"
#include "ui/access_point_chart.h"
#include "ui_mainwindow.h"

#include <QAbstractButton>
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
#include <QtGlobal>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/channel.h>

class QWidget;

namespace {
	const QMap<QString, int> scan_interval_map = {{QT_TR_NOOP("10 seconds"), 10},
	                                              {QT_TR_NOOP("30 seconds"), 30},
	                                              {QT_TR_NOOP("60 seconds"), 60}};

	const int window_content_margin = 5;
	const int toolbar_bottom_margin = 5;
	const int status_message_timeout_ms = 2000;
} // namespace

using namespace KawaiiFi;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _ui(new Ui::MainWindow)
{
	_ui->setupUi(this);

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
	connect(_scan_timer, &QTimer::timeout, this, &MainWindow::scan);
	start_scan_timer(current_scan_interval());
}

MainWindow::~MainWindow() { delete _ui; }

void MainWindow::create_toolbar()
{
	_scan_pause_resume_button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	_scan_pause_resume_button->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
	connect(_scan_pause_resume_button, &QPushButton::clicked, [=]() {
		_scanning_enabled = !_scanning_enabled;
		if (_scanning_enabled) {
			start_scan_timer(current_scan_interval());
			_scan_pause_resume_button->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
		} else {
			stop_scan_timer();
			_scan_pause_resume_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
		}
	});

	_scan_interval_combo_box->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	_scan_interval_combo_box->addItems(scan_interval_map.keys());
	connect(_scan_interval_combo_box, &QComboBox::currentTextChanged, [=]() {
		if (_scanning_enabled) {
			start_scan_timer(current_scan_interval());
		}
	});

	_ap_filter_line_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	_ap_filter_line_edit->setPlaceholderText(tr("Add filter..."));

	_wireless_interface_combo_box->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	QToolBar *toolbar = addToolBar("");
	toolbar->setMovable(false);
	toolbar->setContentsMargins(0, 0, 0, toolbar_bottom_margin);
	toolbar->addWidget(_scan_pause_resume_button);
	toolbar->addWidget(_scan_interval_combo_box);
	toolbar->addWidget(_ap_filter_line_edit);
	toolbar->addWidget(_wireless_interface_combo_box);
}

void MainWindow::create_charts()
{
	_ui->two_four_ghz_chart_view->setChart(_two_point_four_ghz_chart);
	_ui->five_ghz_chart_view->setChart(_five_ghz_chart);
}

void MainWindow::create_table()
{
	_ap_proxy_model->setSourceModel(_ap_table_model);
	_ui->apTableView->setModel(_ap_proxy_model);
	_ui->apTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::set_up_server_interface()
{
	// Register the AccessPoint type with the Qt D-Bus Type System and the Qt meta-type system
	qDBusRegisterMetaType<AccessPoint>();
	qDBusRegisterMetaType<QVector<AccessPoint>>();

	// When a Wi-Fi scan has completed, the server emits a signal
	// Connect that signal to the handle_scan_completed function
	connect(_server_interface, &org::kawaiifi::Server::wifi_scan_completed, this,
	        &MainWindow::handle_scan_completed);
}

void MainWindow::scan()
{
	if (!_server_interface || !_server_interface->isValid()) {
		return;
	}

	_ui->statusBar->showMessage("Starting new scan", status_message_timeout_ms);
	_server_interface->trigger_wifi_scan(_wireless_interface_combo_box->currentText());
}

void MainWindow::handle_scan_completed(const QString &nic_name)
{
	if (!_scanning_enabled || nic_name != _wireless_interface_combo_box->currentText()) {
		return;
	}

	QVector<AccessPoint> aps = _server_interface->access_points(nic_name).value();
	_ap_table_model->update_access_points(aps);
	_two_point_four_ghz_chart->removeAllSeries();
	_five_ghz_chart->removeAllSeries();
	for (const auto &ap : aps) {
		switch (ap.channel().band()) {
		case WifiBand::TwoPointFourGhz:
			_two_point_four_ghz_chart->add_access_point(ap);
			break;
		case WifiBand::FiveGhz:
			_five_ghz_chart->add_access_point(ap);
			break;
		default:
			break;
		}
	}
}

void MainWindow::refresh_wireless_nics()
{
	if (!_server_interface || !_server_interface->isValid()) {
		return;
	}
	// Set wireless nics
	_wireless_interface_combo_box->clear();
	QStringList nic_names = _server_interface->wireless_nic_names().value();
	for (const QString &nic_name : nic_names) {
		_wireless_interface_combo_box->addItem(nic_name);
	}
	_wireless_interface_combo_box->setCurrentIndex(0);
}

int MainWindow::current_scan_interval()
{
	return scan_interval_map[_scan_interval_combo_box->currentText()];
}

void MainWindow::start_scan_timer(int interval_sec)
{
	if (interval_sec > 0) {
		_scan_timer->start(interval_sec * 1000);
	}
}

void MainWindow::stop_scan_timer() { _scan_timer->stop(); }
