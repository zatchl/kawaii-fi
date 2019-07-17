#include "server/server.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	KawaiiFi::Server server;

	// Exit if the server was unable to register itself with D-Bus and acquire a service name
	if (!server.object_registered() || !server.service_name_registered()) {
		return 1;
	}

	return QCoreApplication::exec();
}
