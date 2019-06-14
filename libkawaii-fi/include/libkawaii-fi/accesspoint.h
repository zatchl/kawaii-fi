#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include <QString>

namespace KawaiiFi {
	class AccessPoint {
	public:
		AccessPoint() = default;
		explicit AccessPoint(const QString bssid);

		bool operator==(const AccessPoint &otherAp);
		bool operator!=(const AccessPoint &otherAp);

		const QString bssid() const;
		void setBssid(const QString bssid);

		const QString ssid() const;
		void setSsid(const QString ssid);

		const QString vendor() const;
		void setVendor(const QString vendor);

		int signalStrength() const;
		void setSignalStrength(int signalStrength);

		unsigned int channel() const;
		void setChannel(unsigned int channel);

		unsigned int channelWidth() const;
		void setChannelWidth(unsigned int channelWidth);

	private:
		QString _bssid;
		QString _ssid;
		QString _vendor;
		int _signalStrength;
		unsigned int _channel;
		unsigned int _channelWidth;
	};
} // namespace KawaiiFi

#endif
