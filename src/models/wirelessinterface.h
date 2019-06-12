#ifndef WIRELESSINTERFACE_H
#define WIRELESSINTERFACE_H

#include "accesspoint.h"

#include <QString>
#include <QVector>

namespace KawaiiFi {
	class WirelessInterface {
	public:
		WirelessInterface() = default;
		WirelessInterface(int index, const QString name);
		QString linkStatus() const;
		int triggerScan() const;
		QVector<AccessPoint> scanResults() const;
		QVector<AccessPoint> waitForNewScanResults() const;
		int index() const;
		QString name() const;

	private:
		int _index;
		QString _name;
	};

	QVector<WirelessInterface> getWirelessInterfaces();
} // namespace KawaiiFi

#endif
