#ifndef IE_LENGTH_STANDARD_ITEM_H
#define IE_LENGTH_STANDARD_ITEM_H

#include <QStandardItem>
#include <QVariant>
#include <Qt>

class IeLengthStandardItem : public QStandardItem {
public:
	explicit IeLengthStandardItem(int ie_length);
	[[nodiscard]] QVariant data(int role = Qt::UserRole + 1) const override;
	bool operator<(const QStandardItem &other) const override;
};

#endif // IE_LENGTH_STANDARD_ITEM_H
