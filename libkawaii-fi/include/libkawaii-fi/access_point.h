#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include "capabilities.h"
#include "channel.h"
#include "connection_status.h"
#include "ies/variant.h"
#include "security.h"
#include "standard.h"

#include <QColor>
#include <QMetaType>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QtCore>
#include <array>
#include <linux/nl80211.h>

struct nlattr;

namespace KawaiiFi {
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
		[[nodiscard]] Standards standards() const;
		[[nodiscard]] QStringList supported_rates() const;
		[[nodiscard]] double max_rate() const;
		[[nodiscard]] const Capabilities &capabilities() const;
		[[nodiscard]] const QVector<Ies::Variant> &information_elements() const;

		[[nodiscard]] Channel channel() const;
		[[nodiscard]] const QVector<Security::Protocol> &security() const;
		[[nodiscard]] Security::AkmSuiteType authentication() const;

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
		QVector<Ies::Variant> ies_;
		Channel channel_ = Channel();
		QVector<Security::Protocol> security_;
		Security::AkmSuiteType authentication_ = Security::AkmSuiteType::None;

		unsigned int seen_ms_ago_ = 0;
		unsigned int tsf_ = 0;
		unsigned int beacon_interval_ = 0;
		Standards standards_;
	};

	bool operator==(const AccessPoint &lhs, const AccessPoint &rhs);

	bool operator!=(const AccessPoint &lhs, const AccessPoint &rhs);
} // namespace KawaiiFi

#endif // ACCESS_POINT_H
