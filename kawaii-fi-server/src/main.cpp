#include "server/server.h"

#include <QCoreApplication>
#include <QDBusConnection>
#include <libkawaii-fi/kawaiifi.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	// Exit if the system bus isn't up
	if (!QDBusConnection::systemBus().isConnected()) {
		return 1;
	}

	KawaiiFi::Server server;

	if (!QDBusConnection::systemBus().registerService(KawaiiFi::ServiceName)) {
		return 1;
	}

	return QCoreApplication::exec();
}
