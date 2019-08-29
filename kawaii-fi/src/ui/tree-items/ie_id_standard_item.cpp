#include "ie_id_standard_item.h"

IeIdStandardItem::IeIdStandardItem(unsigned int ie_id) : QStandardItem(1) { setData(ie_id); }

QVariant IeIdStandardItem::data(int role) const
{
	if (role == Qt::DisplayRole) {
		return data().toString();
	}
	return QStandardItem::data(role);
}

bool IeIdStandardItem::operator<(const QStandardItem &other) const
{
	return data().toUInt() < other.data().toUInt();
}
