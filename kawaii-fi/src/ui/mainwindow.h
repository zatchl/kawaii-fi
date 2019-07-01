#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "kawaiifi_server_interface.h"
#include "models/access_point_table_model.h"

#include <QMainWindow>
#include <QProgressBar>
#include <QString>

namespace KawaiiFi {
	namespace Ui {
		class MainWindow;
	}

	class MainWindow : public QMainWindow {
		Q_OBJECT
	public:
		explicit MainWindow(QWidget *parent = nullptr);
		~MainWindow();
		void connect_to_server();

	private:
		void scan();
		void handle_scan_completed(const QString &nic_name);
		void refresh_wireless_nics();
		Ui::MainWindow *_ui;
		QProgressBar *_progress_bar;
		org::kawaiifi::Server *_server_interface = nullptr;
		AccessPointTableModel *_ap_table_model = nullptr;
	};
} // namespace KawaiiFi

#endif // MAINWINDOW_H
