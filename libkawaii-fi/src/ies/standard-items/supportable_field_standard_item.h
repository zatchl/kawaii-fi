#ifndef SUPPORTABLE_FIELD_STANDARD_ITEM_H
#define SUPPORTABLE_FIELD_STANDARD_ITEM_H

#include <QList>
#include <QStandardItem>
#include <QString>

namespace KawaiiFi::Ies {
	class SupportableFieldStandardItem : public QStandardItem {
	public:
		explicit SupportableFieldStandardItem(bool supportable_field);
	};

	QList<QStandardItem *> supportable_field_row(const QString &title, bool supportable_field);
} // namespace KawaiiFi::Ies

#endif // SUPPORTABLE_FIELD_STANDARD_ITEM_H
