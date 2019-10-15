#include "protocol_filter_menu.h"

#include "ui/filter-menus/access_point_filter_menu.h"

#include <QSet>
#include <QVariant>
#include <QVector>
#include <libkawaii-fi/access_point.h>

class QWidget;

ProtocolFilterMenu::ProtocolFilterMenu(QWidget *parent) : AccessPointFilterMenu("Protocol", parent)
{
	add_filter_check_box("802.11b", QVariant::fromValue(KawaiiFi::Standard::B));
	add_filter_check_box("802.11g", QVariant::fromValue(KawaiiFi::Standard::G));
	add_filter_check_box("802.11n", QVariant::fromValue(KawaiiFi::Standard::N));
	add_filter_check_box("802.11a", QVariant::fromValue(KawaiiFi::Standard::A));
	add_filter_check_box("802.11ac", QVariant::fromValue(KawaiiFi::Standard::AC));
	add_filter_check_box("802.11ax", QVariant::fromValue(KawaiiFi::Standard::AX));
}

KawaiiFi::Standards ProtocolFilterMenu::standards() const
{
	KawaiiFi::Standards protocols;
	const auto check_boxes = checked_filter_check_boxes();
	for (const auto check_box : check_boxes) {
		protocols.setFlag(check_box->data().value<KawaiiFi::Standard>());
	}
	return protocols;
}
