#include "ui/mainwindow.h"
#include <QApplication>

using namespace KawaiiFi;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return QApplication::exec();
}
