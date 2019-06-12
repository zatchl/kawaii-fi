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
		bool supportsTwoPointFourGhz() const;
		bool supportsFiveGhz() const;
		int index() const;
		QString name() const;
		QVector<unsigned int> twoPointFourGhzChannels() const;
		QVector<unsigned int> fiveGhzChannels() const;

	private:
		int _index;
		QString _name;
		QVector<unsigned int> _twoPointFourGhzChannels;
		QVector<unsigned int> _fiveGhzChannels;
	};

	QVector<WirelessInterface> getWirelessInterfaces();
} // namespace KawaiiFi

#endif
