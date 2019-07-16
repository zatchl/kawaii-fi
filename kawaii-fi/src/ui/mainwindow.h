#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "kawaiifi_server_interface.h"
#include "models/access_point_table_model.h"
#include "ui/access_point_chart.h"

#include <QByteArrayData>
#include <QComboBox>
#include <QDBusConnection>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QString>
#include <QTimer>
#include <libkawaii-fi/channel.h>
#include <libkawaii-fi/kawaiifi.h>

class QObject;
class QWidget;

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
		int current_scan_interval();
		void start_scan_timer(int interval_sec);
		void stop_scan_timer();
		Ui::MainWindow *ui_;
		bool scanning_enabled_ = true;
		QPushButton *const scan_pause_resume_button_ = new QPushButton(this);
		QComboBox *const scan_interval_combo_box_ = new QComboBox(this);
		QLineEdit *const ap_filter_line_edit_ = new QLineEdit(this);
		QComboBox *const wireless_interface_combo_box_ = new QComboBox(this);
		AccessPointTableModel *const ap_table_model_ = new AccessPointTableModel(this);
		QSortFilterProxyModel *const ap_proxy_model_ = new QSortFilterProxyModel(this);
		AccessPointChart *const two_point_four_ghz_chart_ =
		        new AccessPointChart(WifiBand::TwoPointFourGhz);
		AccessPointChart *const five_ghz_chart_ = new AccessPointChart(WifiBand::FiveGhz);
		QTimer *const scan_timer_ = new QTimer(this);
		org::kawaiifi::Server *const server_interface_ =
		        new org::kawaiifi::Server(KawaiiFi::ServiceName, KawaiiFi::ServerObjectPath,
		                                  QDBusConnection::systemBus(), this);
	};
} // namespace KawaiiFi

#endif // MAINWINDOW_H
