#include "libkawaii-fi/ies/standard-items/ie_length_standard_item.h"

#include <QString>

namespace KawaiiFi::Ies {
	IeLengthStandardItem::IeLengthStandardItem(int ie_length) { setData(ie_length); }

	QVariant IeLengthStandardItem::data(int role) const
	{
		if (role == Qt::DisplayRole) {
			return QString("%0 bytes").arg(data().toString());
		}
		return QStandardItem::data(role);
	}

	bool IeLengthStandardItem::operator<(const QStandardItem &other) const
	{
		return data().toInt() < other.data().toInt();
	}
} // namespace KawaiiFi::Ies
