#include "mainwindow.h"

#include "kawaiifi_server_interface.h"
#include "models/access_point_table_model.h"
#include "ui_mainwindow.h"

#include <QChartView>
#include <QComboBox>
#include <QDBusConnection>
#include <QDBusObjectPath>
#include <QMainWindow>
#include <QProgressBar>
#include <QSortFilterProxyModel>
#include <QString>
#include <QTableView>
#include <QTimer>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/kawaiifi.h>

using namespace KawaiiFi;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _ui(new Ui::MainWindow)
{
	_ui->setupUi(this);
	_ui->scanIntervalComboBox->addItems(QStringList({"10 seconds", "30 seconds", "1 minute"}));

	// Remove the rounded corners around the chart view
	_ui->apSpectrumChartView->chart()->layout()->setContentsMargins(0, 0, 0, 0);

	// Divide the splitter in half
	_ui->splitter->setSizes({INT_MAX, INT_MAX});

	_ap_table_model = new AccessPointTableModel(this);
	_ap_proxy_model = new QSortFilterProxyModel(this);
	_ap_proxy_model->setSourceModel(_ap_table_model);

	_ui->apTableView->setModel(_ap_proxy_model);
	_ui->apTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	_ui->scanButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
	set_up_server_interface();

	_ui->filterLineEdit->setFocus();

	_progress_bar = new QProgressBar();
	_progress_bar->setRange(0, 0);
	statusBar()->addPermanentWidget(_progress_bar);
	_progress_bar->hide();
}

MainWindow::~MainWindow() { delete _ui; }

{
	if (_server_interface && _server_interface->isValid()) {
		return;
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
	_progress_bar->show();
	_server_interface->trigger_wifi_scan(_ui->interfaceComboBox->currentText());
}

void MainWindow::handle_scan_completed(const QString &nic_name)
{
	if (_server_interface && nic_name == _ui->interfaceComboBox->currentText()) {
		_ap_table_model->update_access_points(_server_interface->access_points(nic_name).value());
	}

	_ui->interfaceComboBox->setEnabled(true);
	_progress_bar->hide();

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
