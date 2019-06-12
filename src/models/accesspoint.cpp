#include "accesspoint.h"

#include <QString>

namespace KawaiiFi {
	AccessPoint::AccessPoint(const QString bssid) : _bssid(bssid)
	{
	}

	bool AccessPoint::operator==(const AccessPoint &otherAp)
	{
		return _bssid == otherAp.bssid();
	}

	bool AccessPoint::operator!=(const AccessPoint &otherAp)
	{
		return !(*this == otherAp);
	}

	const QString AccessPoint::bssid() const
	{
		return _bssid;
	}

	void AccessPoint::setBssid(const QString bssid)
	{
		_bssid = bssid;
	}

	const QString AccessPoint::ssid() const
	{
		return _ssid;
	}

	void AccessPoint::setSsid(const QString ssid)
	{
		_ssid = ssid;
	}

	const QString AccessPoint::vendor() const
	{
		return _vendor;
	}

	void AccessPoint::setVendor(const QString vendor)
	{
		_vendor = vendor;
	}

	int AccessPoint::signalStrength() const
	{
		return _signalStrength;
	}

	void AccessPoint::setSignalStrength(int signalStrength)
	{
		_signalStrength = signalStrength;
	}

	unsigned int AccessPoint::channel() const
	{
		return _channel;
	}

	void AccessPoint::setChannel(unsigned int channel)
	{
		_channel = channel;
	}

	unsigned int AccessPoint::channelWidth() const
	{
		return _channelWidth;
	}

	void AccessPoint::setChannelWidth(unsigned int channelWidth)
	{
		_channelWidth = channelWidth;
	}
} // namespace KawaiiFi
