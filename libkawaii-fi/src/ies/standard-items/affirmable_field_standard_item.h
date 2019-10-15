#ifndef AFFIRMABLE_FIELD_STANDARD_ITEM_H
#define AFFIRMABLE_FIELD_STANDARD_ITEM_H

#include <QList>
#include <QStandardItem>
#include <QString>

namespace KawaiiFi::Ies {
	class AffirmableFieldStandardItem : public QStandardItem {
	public:
		explicit AffirmableFieldStandardItem(bool affirmable_field);
	};

	QList<QStandardItem *> affirmable_field_row(const QString &title, bool affirmable_field);
} // namespace KawaiiFi::Ies

#endif // AFFIRMABLE_FIELD_STANDARD_ITEM_H
