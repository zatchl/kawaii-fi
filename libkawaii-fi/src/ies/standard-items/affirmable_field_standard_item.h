#ifndef AFFIRMABLE_FIELD_STANDARD_ITEM_H
#define AFFIRMABLE_FIELD_STANDARD_ITEM_H

#include <QList>
#include <QStandardItem>
#include <QString>

class AffirmableFieldStandardItem : public QStandardItem {
public:
	AffirmableFieldStandardItem(bool affirmable_field);
};

QList<QStandardItem *> affirmable_field_row(const QString &title, bool affirmable_field);

#endif // AFFIRMABLE_FIELD_STANDARD_ITEM_H
