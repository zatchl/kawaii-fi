#include "mainwindow.h"

#include "kawaiifi_server_interface.h"
#include "models/access_point_table_model.h"
#include "ui/access_point_chart.h"
#include "ui_mainwindow.h"

#include <QChartView>
#include <QComboBox>
#include <QDBusConnection>
#include <QDBusObjectPath>
#include <QMainWindow>
#include <QMap>
#include <QString>
#include <QTableView>
#include <QTimer>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/kawaiifi.h>

namespace {
	const QMap<QString, int> scan_interval_map = {{QT_TR_NOOP("10 seconds"), 10},
	                                              {QT_TR_NOOP("30 seconds"), 30},
	                                              {QT_TR_NOOP("60 seconds"), 60}};

	const int toolbar_bottom_margin = 5;
} // namespace

using namespace KawaiiFi;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _ui(new Ui::MainWindow)
{
	_ui->setupUi(this);

	// Divide the splitter in half
	_ui->splitter->setSizes({INT_MAX, INT_MAX});

	create_toolbar();
	create_charts();
	create_table();

	set_up_server_interface();


void MainWindow::create_toolbar()
{
	_scan_pause_resume_button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	_scan_pause_resume_button->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
	connect(_scan_pause_resume_button, &QPushButton::clicked, [=]() {
	});

	_scan_interval_combo_box->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	_scan_interval_combo_box->addItems(scan_interval_map.keys());
	connect(_scan_interval_combo_box, &QComboBox::currentTextChanged, [=]() {
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

MainWindow::~MainWindow() { delete _ui; }
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

	_ui->interfaceComboBox->setEnabled(false);
	_server_interface->trigger_wifi_scan(_ui->interfaceComboBox->currentText());
}

void MainWindow::handle_scan_completed(const QString &nic_name)
{
	if (_server_interface && nic_name == _ui->interfaceComboBox->currentText()) {
		_ap_table_model->update_access_points(_server_interface->access_points(nic_name).value());
	}

	_ui->interfaceComboBox->setEnabled(true);

	QTimer::singleShot(10000, this, &MainWindow::scan);
}

void MainWindow::refresh_wireless_nics()
{
	if (!_server_interface || !_server_interface->isValid()) {
		return;
	}
	// Set wireless nics
	_ui->interfaceComboBox->clear();
	QStringList nic_names = _server_interface->wireless_nic_names().value();
	for (const QString &nic_name : nic_names) {
		_ui->interfaceComboBox->addItem(nic_name);
	}
	_ui->interfaceComboBox->setCurrentIndex(0);
}
