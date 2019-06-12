#include "wirelessinterface.h"
#include "accesspoint.h"

#include <QString>
#include <QVector>
#include <net/if.h>

namespace KawaiiFi {
	WirelessInterface::WirelessInterface(int index, const QString name) : _index(index), _name(name)
	{
	}

	QString WirelessInterface::linkStatus() const
	{
		return "";
	}

	int WirelessInterface::triggerScan() const
	{
		return 0;
	}

	QVector<AccessPoint> WirelessInterface::scanResults() const
	{
		QVector<AccessPoint> accessPoints;
		return accessPoints;
	}

	QVector<AccessPoint> WirelessInterface::waitForNewScanResults() const
	{
		triggerScan();
		return scanResults();
	}

	QString WirelessInterface::name() const
	{
		return _name;
	}

	int WirelessInterface::index() const
	{
		return _index;
	}

	QVector<WirelessInterface> getWirelessInterfaces()
	{
		QVector<WirelessInterface> wirelessInterfaces;
		return wirelessInterfaces;
	}
} // namespace KawaiiFi
