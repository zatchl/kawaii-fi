#include "ui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	KawaiiFi::MainWindow w;
	w.show();
	w.connect_to_server();

	return QApplication::exec();
}
