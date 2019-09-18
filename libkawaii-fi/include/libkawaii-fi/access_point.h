#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include "capabilities.h"
#include "channel.h"
#include "connection_status.h"
#include "ies/ie_variant.h"
#include "security.h"

#include <QColor>
#include <QFlags>
#include <QMetaType>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QtCore>
#include <array>
#include <linux/nl80211.h>

struct nlattr;

enum class Protocol { B = 1 << 0, A = 1 << 1, G = 1 << 2, N = 1 << 3, AC = 1 << 4, AX = 1 << 5 };

Q_DECLARE_METATYPE(Protocol)
Q_DECLARE_FLAGS(Protocols, Protocol)
Q_DECLARE_OPERATORS_FOR_FLAGS(Protocols)

inline uint qHash(Protocol key, uint seed) { return qHash(static_cast<int>(key), seed); }

class AccessPoint {
public:
	AccessPoint() = default;
	AccessPoint(QString bssid, const std::array<nlattr *, NL80211_BSS_MAX + 1> &bss);

	[[nodiscard]] const QString &bssid() const;
	[[nodiscard]] const QString &ssid() const;
	[[nodiscard]] const QColor &color() const;
	[[nodiscard]] ConnectionStatus connection_status() const;
	[[nodiscard]] double signal_dbm() const;
	[[nodiscard]] unsigned int frequency() const;
	[[nodiscard]] unsigned int age_ms() const;
	[[nodiscard]] Protocols protocols() const;
	[[nodiscard]] QStringList supported_rates() const;
	[[nodiscard]] double max_rate() const;
	[[nodiscard]] const Capabilities &capabilities() const;
	[[nodiscard]] const QVector<IeVariant> &information_elements() const;

	[[nodiscard]] ChannelWidth channel_width() const;
	[[nodiscard]] Channel channel() const;
	[[nodiscard]] const QVector<SecurityProtocol> &security() const;
	[[nodiscard]] AkmSuiteType authentication() const;

	void update_data(const std::array<nlattr *, NL80211_BSS_MAX + 1> &bss);

private:
	const QString bssid_;
	QString ssid_;
	const QColor color_;
	ConnectionStatus connection_status_ = ConnectionStatus::Unknown;
	double signal_dbm_ = 0;
	unsigned int frequency_ = 0;
	unsigned int age_ms_ = 0;

	QStringList supported_rates_;
	double max_rate_ = 0;
	Capabilities capabilities_;
	QVector<IeVariant> ies_;
	ChannelWidth channel_width_ = ChannelWidth::TwentyMhz;
	Channel channel_ = Channel();
	QVector<SecurityProtocol> security_;
	AkmSuiteType authentication_ = AkmSuiteType::None;

	unsigned int seen_ms_ago_ = 0;
	unsigned int tsf_ = 0;
	unsigned int beacon_interval_ = 0;
	Protocols protocols_;
};

bool operator==(const AccessPoint &lhs, const AccessPoint &rhs);

bool operator!=(const AccessPoint &lhs, const AccessPoint &rhs);

#endif // ACCESS_POINT_H
