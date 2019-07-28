#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include "capabilities.h"
#include "channel.h"
#include "information_element.h"

#include <QDBusArgument>
#include <QHashNode>
#include <QMetaType>
#include <QString>
#include <QVector>
#include <array>

enum class ConnectionStatus { Authenticated, Associated, Joined, Unknown };

enum class Protocol { B, A, G, N, AC, AX };

enum class Security { None, WEP, WPA, WPA2, WPA3 };

class AccessPoint {
public:
	[[nodiscard]] const QString &bssid() const;
	[[nodiscard]] ConnectionStatus connection_status() const;
	[[nodiscard]] int signal_strength_mbm() const;
	[[nodiscard]] double signal_strength_dbm() const;
	[[nodiscard]] unsigned int frequency() const;
	[[nodiscard]] unsigned int age_ms() const;
	[[nodiscard]] const QVector<Protocol> &protocols() const;
	[[nodiscard]] QVector<Protocol> &protocols();
	[[nodiscard]] const Capabilities &capabilities() const;
	[[nodiscard]] Capabilities &capabilites();
	[[nodiscard]] const QMultiHash<unsigned int, InformationElement> &information_elements() const;
	[[nodiscard]] QMultiHash<unsigned int, InformationElement> &information_elements();
	[[nodiscard]] bool contains_vendor_element(const std::array<unsigned char, 3> &oui,
	                                           unsigned int type) const;
	[[nodiscard]] ChannelWidth channel_width() const;
	[[nodiscard]] Channel channel() const;
	[[nodiscard]] QVector<Security> security() const;

	void set_bssid(const QString &bssid);
	void set_connection_status(ConnectionStatus connection_status);
	void set_signal_strength_mbm(int signal_strength_mbm);
	void set_frequency(unsigned int frequency);
	void set_age_ms(unsigned int age_ms);
	void set_capabilities(const char *bytes, int size);
	void set_protocols(const QVector<Protocol> &protocols);

private:
	QString bssid_;
	ConnectionStatus connection_status_ = ConnectionStatus::Unknown;
	int signal_strength_mbm_ = 0;
	unsigned int frequency_ = 0;
	unsigned int age_ms_ = 0;
	QVector<Protocol> protocols_;
	Capabilities capabilities_;
	QMultiHash<unsigned int, InformationElement> information_elements_;
};
Q_DECLARE_METATYPE(AccessPoint)

// Marshall the AccessPoint data into a D-Bus argument
QDBusArgument &operator<<(QDBusArgument &argument, const AccessPoint &ap);

// Retrieve the AccessPoint data from the D-Bus argument
const QDBusArgument &operator>>(const QDBusArgument &argument, AccessPoint &ap);

bool operator==(const AccessPoint &lhs, const AccessPoint &rhs);

bool operator!=(const AccessPoint &lhs, const AccessPoint &rhs);

#endif // ACCESS_POINT_H
