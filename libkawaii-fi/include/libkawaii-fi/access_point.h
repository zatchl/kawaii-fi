#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include "capabilities.h"
#include "channel.h"
#include "connection_status.h"
#include "ies/ie_variant.h"
#include "security.h"

#include <QDBusArgument>
#include <QColor>
#include <QMetaType>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QtCore>
#include <array>


enum class Protocol { B, A, G, N, AC, AX };

Q_DECLARE_METATYPE(Protocol)

inline uint qHash(Protocol key, uint seed) { return qHash(static_cast<int>(key), seed); }

class AccessPoint {
public:
	[[nodiscard]] const QString &bssid() const;
	[[nodiscard]] QString ssid() const;
	[[nodiscard]] const QColor &color() const;
	[[nodiscard]] ConnectionStatus connection_status() const;
	[[nodiscard]] int signal_strength_mbm() const;
	[[nodiscard]] double signal_strength_dbm() const;
	[[nodiscard]] unsigned int frequency() const;
	[[nodiscard]] unsigned int age_ms() const;
	[[nodiscard]] const QVector<Protocol> &protocols() const;
	[[nodiscard]] QVector<Protocol> &protocols();
	[[nodiscard]] QStringList supported_rates() const;
	[[nodiscard]] double max_rate() const;
	[[nodiscard]] const Capabilities &capabilities() const;
	[[nodiscard]] Capabilities &capabilites();
	[[nodiscard]] const QVector<IeVariant> &information_elements() const;

	[[nodiscard]] ChannelWidth channel_width() const;
	[[nodiscard]] Channel channel() const;
	[[nodiscard]] QVector<SecurityProtocol> security() const;
	[[nodiscard]] AkmSuiteType authentication() const;

	void set_bssid(const QString &bssid);
	void set_connection_status(ConnectionStatus connection_status);
	void set_signal_strength_mbm(int signal_strength_mbm);
	void set_frequency(unsigned int frequency);
	void set_age_ms(unsigned int age_ms);
	void set_capabilities(const char *bytes, int size);
	void set_protocols(const QVector<Protocol> &protocols);

private:
	QString bssid_;
	const QColor color_;
	ConnectionStatus connection_status_ = ConnectionStatus::Unknown;
	int signal_strength_mbm_ = 0;
	unsigned int frequency_ = 0;
	unsigned int age_ms_ = 0;
	QVector<Protocol> protocols_;
	Capabilities capabilities_;
};
Q_DECLARE_METATYPE(AccessPoint)

// Marshall the AccessPoint data into a D-Bus argument
QDBusArgument &operator<<(QDBusArgument &argument, const AccessPoint &ap);
	QVector<IeVariant> ies_;

// Retrieve the AccessPoint data from the D-Bus argument
const QDBusArgument &operator>>(const QDBusArgument &argument, AccessPoint &ap);

bool operator==(const AccessPoint &lhs, const AccessPoint &rhs);

bool operator!=(const AccessPoint &lhs, const AccessPoint &rhs);

#endif // ACCESS_POINT_H
