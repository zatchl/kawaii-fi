#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "kawaiifi_server_interface.h"
#include "models/access_point_table_model.h"

#include <QComboBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QString>
#include <libkawaii-fi/kawaiifi.h>

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
		void create_toolbar();
		void set_up_server_interface();
		void scan();
		void handle_scan_completed(const QString &nic_name);
		void refresh_wireless_nics();
		Ui::MainWindow *_ui;
		QProgressBar *_progress_bar;
		AccessPointTableModel *_ap_table_model = nullptr;
		QSortFilterProxyModel *_ap_proxy_model = nullptr;
		org::kawaiifi::Server *const _server_interface =
		        new org::kawaiifi::Server(KawaiiFi::ServiceName, KawaiiFi::ServerObjectPath,
		                                  QDBusConnection::systemBus(), this);
	};
} // namespace KawaiiFi

#endif // MAINWINDOW_H
