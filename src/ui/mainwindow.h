#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "models/accesspoint.h"
#include "models/wirelessinterface.h"

#include <QFutureWatcher>
#include <QMainWindow>
#include <QProgressBar>

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
	};
} // namespace KawaiiFi

#endif // MAINWINDOW_H
