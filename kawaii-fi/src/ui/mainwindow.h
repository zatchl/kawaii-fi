#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scanning/access_point_scanner.h"

#include <QByteArrayData>
#include <QMainWindow>
#include <QString>

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
		Ui::MainWindow *ui_;
		AccessPointScanner *const scanner_ = new AccessPointScanner(this);

		void populate_menu_bar();
		void pause_scanning();
		void resume_scanning();
		QString selected_wireless_interface() const;
	};
} // namespace KawaiiFi

#endif // MAINWINDOW_H
