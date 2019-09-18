#include "protocol_filter_menu.h"

#include "ui/filter-menus/access_point_filter_menu.h"

#include <QSet>
#include <QVariant>
#include <QVector>
#include <libkawaii-fi/access_point.h>

class QWidget;

ProtocolFilterMenu::ProtocolFilterMenu(QWidget *parent) : AccessPointFilterMenu("Protocol", parent)
{
	add_filter_check_box("802.11b", QVariant::fromValue(Protocol::B));
	add_filter_check_box("802.11g", QVariant::fromValue(Protocol::G));
	add_filter_check_box("802.11n", QVariant::fromValue(Protocol::N));
	add_filter_check_box("802.11a", QVariant::fromValue(Protocol::A));
	add_filter_check_box("802.11ac", QVariant::fromValue(Protocol::AC));
	add_filter_check_box("802.11ax", QVariant::fromValue(Protocol::AX));
}

QSet<Protocol> ProtocolFilterMenu::protocols() const
{
	QSet<Protocol> protocols;
	for (const auto check_box : checked_filter_check_boxes()) {
		protocols.insert(check_box->data().value<Protocol>());
	}
	return protocols;
}
