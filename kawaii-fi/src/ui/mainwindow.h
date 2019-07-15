#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "kawaiifi_server_interface.h"
#include "models/access_point_table_model.h"
#include "ui/access_point_chart.h"

#include <QComboBox>
#include <QLineEdit>
#include <QMainWindow>
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
		void create_charts();
		void create_table();
		void set_up_server_interface();
		void scan();
		void handle_scan_completed(const QString &nic_name);
		void refresh_wireless_nics();
		Ui::MainWindow *_ui;
		QPushButton *const _scan_pause_resume_button = new QPushButton(this);
		QComboBox *const _scan_interval_combo_box = new QComboBox(this);
		QLineEdit *const _ap_filter_line_edit = new QLineEdit(this);
		QComboBox *const _wireless_interface_combo_box = new QComboBox(this);
		AccessPointTableModel *const _ap_table_model = new AccessPointTableModel(this);
		QSortFilterProxyModel *const _ap_proxy_model = new QSortFilterProxyModel(this);
		AccessPointChart *const _two_point_four_ghz_chart =
		        new AccessPointChart(WifiBand::TwoPointFourGhz);
		AccessPointChart *const _five_ghz_chart = new AccessPointChart(WifiBand::FiveGhz);
		org::kawaiifi::Server *const _server_interface =
		        new org::kawaiifi::Server(KawaiiFi::ServiceName, KawaiiFi::ServerObjectPath,
		                                  QDBusConnection::systemBus(), this);
	};
} // namespace KawaiiFi

#endif // MAINWINDOW_H
