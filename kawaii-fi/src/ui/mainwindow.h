#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "models/accesspointtablemodel.h"

#include <QFutureWatcher>
#include <QMainWindow>
#include <QProgressBar>
#include <libkawaii-fi/accesspoint.h>
#include <libkawaii-fi/wirelessinterface.h>

namespace KawaiiFi {
	namespace Ui {
		class MainWindow;
	}

	class MainWindow : public QMainWindow {
		Q_OBJECT
	public:
		explicit MainWindow(QWidget *parent = nullptr);
		~MainWindow();

	private:
		void scan();
		void handleScanResult();
		Ui::MainWindow *_ui;
		QProgressBar *_progressBar;
		QFutureWatcher<QVector<KawaiiFi::AccessPoint>> _scanResultWatcher;
		QVector<KawaiiFi::WirelessInterface> _wirelessInterfaces;
		AccessPointTableModel *_apTableModel;
	};
} // namespace KawaiiFi

#endif // MAINWINDOW_H
