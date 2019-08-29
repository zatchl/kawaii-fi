#ifndef SUPPORTABLE_FIELD_STANDARD_ITEM_H
#define SUPPORTABLE_FIELD_STANDARD_ITEM_H

#include <QList>
#include <QStandardItem>
#include <QString>

class SupportableFieldStandardItem : public QStandardItem {
public:
	SupportableFieldStandardItem(bool supportable_field);
};

QList<QStandardItem *> supportable_field_row(const QString &title, bool supportable_field);

#endif // SUPPORTABLE_FIELD_STANDARD_ITEM_H
