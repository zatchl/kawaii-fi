#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scanning/access_point_scanner.h"
#include "ui/access_point_table.h"

#include <QByteArrayData>
#include <QMainWindow>
#include <QString>
#include <QTimer>

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
		AccessPointTableView *const table_view_ = new AccessPointTableView(*scanner_, this);
		QTimer *const scan_timer_ = new QTimer(this);
	};
} // namespace KawaiiFi

#endif // MAINWINDOW_H
