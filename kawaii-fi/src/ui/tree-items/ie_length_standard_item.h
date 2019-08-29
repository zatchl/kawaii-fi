#ifndef IE_LENGTH_STANDARD_ITEM_H
#define IE_LENGTH_STANDARD_ITEM_H

#include <QStandardItem>
#include <QVariant>
#include <Qt>

class IeLengthStandardItem : public QStandardItem {
public:
	IeLengthStandardItem(int ie_length);
	virtual QVariant data(int role = Qt::UserRole + 1) const override;
	virtual bool operator<(const QStandardItem &other) const override;
};

#endif // IE_LENGTH_STANDARD_ITEM_H
