#include "affirmable_field_standard_item.h"

AffirmableFieldStandardItem::AffirmableFieldStandardItem(bool affirmable_field)
    : QStandardItem(affirmable_field ? "True" : "False")
{
}

QList<QStandardItem *> affirmable_field_row(const QString &title, bool affirmable_field)
{
	return {new QStandardItem(title), new AffirmableFieldStandardItem(affirmable_field)};
}
