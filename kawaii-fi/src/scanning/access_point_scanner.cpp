#include "access_point_scanner.h"

#include <QColor>
#include <QDBusPendingReply>
#include <QVector>
#include <QtDBus>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/ies/information_element.h>

namespace {
	const QVector<QColor> colors = {
	        QColor(191, 97, 106),  QColor(208, 135, 112), QColor(163, 190, 140),
	        QColor(180, 142, 173), QColor(94, 129, 172),  QColor(235, 203, 139),
	        QColor(76, 86, 106),   QColor(143, 188, 187), QColor(222, 53, 106),
	        QColor(33, 101, 131),  QColor(255, 185, 97),  QColor(200, 218, 211),
	        QColor(75, 63, 114),   QColor(105, 113, 117), QColor(168, 218, 220),
	        QColor(229, 89, 52),   QColor(242, 181, 212), QColor(50, 147, 111),
	        QColor(191, 239, 69),  QColor(66, 212, 244),  QColor(228, 182, 96),
	        QColor(29, 106, 150),  QColor(155, 207, 184), QColor(188, 95, 106),
	        QColor(80, 78, 99),    QColor(154, 27, 39),   QColor(107, 121, 158),
	        QColor(10, 91, 84),    QColor(217, 207, 231), QColor(255, 162, 137),
	        QColor(112, 111, 171), QColor(157, 30, 49),   QColor(122, 45, 89),
	        QColor(55, 65, 154),   QColor(235, 151, 114), QColor(105, 93, 133),
	        QColor(166, 194, 206)};
	int color_index = 0;
} // namespace

AccessPointScanner::AccessPointScanner(QObject *parent) : QObject(parent)
{
	// Register the AccessPoint and InformationElement types with the Qt D-Bus type system and the
	// Qt meta type system
	qDBusRegisterMetaType<AccessPoint>();
	qDBusRegisterMetaType<QVector<AccessPoint>>();
	qDBusRegisterMetaType<InformationElement>();

	connect(server_, &org::kawaiifi::Server::wifi_scan_completed, [this](const QString &nic) {
		if (nic != interface_name_) {
			return;
		}
		access_points_ = server_->access_points(interface_name_).value();
		for (const auto &ap : access_points_) {
			if (access_point_colors_.contains(ap.bssid())) {
				continue;
			}
			access_point_colors_[ap.bssid()] = colors[color_index++];
			if (color_index >= colors.size()) {
				color_index = 0;
			}
		}
		emit access_points_updated(nic);
	});
}

void AccessPointScanner::scan(const QString &interface_name)
{
	if (!interface_name.isEmpty()) {
		interface_name_ = interface_name;
	}
	server_->trigger_wifi_scan(interface_name);
}

const QVector<AccessPoint> &AccessPointScanner::access_points() const { return access_points_; }

QHash<QString, QColor> AccessPointScanner::access_point_colors() const
{
	return access_point_colors_;
}

QStringList AccessPointScanner::wireless_nic_names() const
{
	return server_->wireless_nic_names().value();
}
