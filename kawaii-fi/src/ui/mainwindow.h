#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QByteArrayData>
#include <QMainWindow>
#include <QString>
#include <libkawaii-fi/scanning/access_point_scanner.h>

class QObject;
class QWidget;

namespace Ui {
	class MainWindow;
} // namespace Ui

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui_;
	KawaiiFi::Scanning::AccessPointScanner *const scanner_ =
	        new KawaiiFi::Scanning::AccessPointScanner(this);

	void populate_menu_bar();
	void pause_scanning();
	void resume_scanning();
	[[nodiscard]] QString selected_wireless_interface() const;
};

#endif // MAINWINDOW_H
