#ifndef IE_ID_STANDARD_ITEM_H
#define IE_ID_STANDARD_ITEM_H

#include <QStandardItem>
#include <QVariant>
#include <Qt>

class IeIdStandardItem : public QStandardItem {
public:
	explicit IeIdStandardItem(unsigned int ie_id);
	[[nodiscard]] QVariant data(int role = Qt::UserRole + 1) const override;
	bool operator<(const QStandardItem &other) const override;
};

#endif // IE_ID_STANDARD_ITEM_H
