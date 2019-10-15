#include "supportable_field_standard_item.h"

namespace KawaiiFi::Ies {
	SupportableFieldStandardItem::SupportableFieldStandardItem(bool supportable_field)
	    : QStandardItem(supportable_field ? "Supported" : "Not Supported")
	{
	}

	QList<QStandardItem *> supportable_field_row(const QString &title, bool supportable_field)
	{
		return {new QStandardItem(title), new SupportableFieldStandardItem(supportable_field)};
	}
} // namespace KawaiiFi::Ies
