#include "ui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	KawaiiFi::MainWindow w;
	w.show();

	return QApplication::exec();
}
