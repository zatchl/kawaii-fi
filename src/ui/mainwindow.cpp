#include "mainwindow.h"
#include "models/accesspoint.h"
#include "models/accesspointtablemodel.h"
#include "models/wirelessinterface.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QFuture>
#include <QFutureWatcher>
#include <QMainWindow>
#include <QProgressBar>
#include <QTimer>
#include <QVector>
#include <QtConcurrent/QtConcurrentRun>

using namespace KawaiiFi;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _ui(new Ui::MainWindow)
{
	_ui->setupUi(this);
	_ui->scanIntervalComboBox->addItems(QStringList({"10 seconds", "30 seconds", "1 minute"}));

	_wirelessInterfaces = KawaiiFi::getWirelessInterfaces();
	for (const auto &interface : _wirelessInterfaces) {
		_ui->interfaceComboBox->addItem(interface.name());
	}

	_ui->apSpectrumChartView->chart()->layout()->setContentsMargins(0, 0, 0, 0);

	_ui->splitter->setSizes({INT_MAX, INT_MAX});

	_apTableModel = new AccessPointTableModel(this);
	_ui->apTableView->setModel(_apTableModel);
	_ui->apTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	connect(&_scanResultWatcher, &QFutureWatcher<QVector<KawaiiFi::AccessPoint>>::finished, this,
	        &MainWindow::handleScanResult);

	_progressBar = new QProgressBar();
	_progressBar->setRange(0, 0);
	statusBar()->addPermanentWidget(_progressBar);
	_progressBar->hide();
	scan();
}

MainWindow::~MainWindow()
{
	delete _ui;
}

void MainWindow::scan()
{
	if (_wirelessInterfaces.size() > 0) {
		_progressBar->show();
		QFuture<QVector<KawaiiFi::AccessPoint>> scanResult =
		        QtConcurrent::run(_wirelessInterfaces[_ui->interfaceComboBox->currentIndex()],
		                &KawaiiFi::WirelessInterface::waitForNewScanResults);
		_scanResultWatcher.setFuture(scanResult);
	}
}

void MainWindow::handleScanResult()
{
	_progressBar->hide();
	statusBar()->showMessage(
	        QString("Found %0 access points").arg(_scanResultWatcher.result().size()));
	_apTableModel->updateAccessPoints(_scanResultWatcher.result());
	QTimer::singleShot(5000, this, &MainWindow::scan);
}
