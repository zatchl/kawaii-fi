#ifndef RSN_STANDARD_ITEM_H
#define RSN_STANDARD_ITEM_H

#include <QStandardItem>

class RobustSecurityNetwork;

class RsnStandardItem : public QStandardItem {
public:
	explicit RsnStandardItem(const RobustSecurityNetwork &rsn);
};

#endif // RSN_STANDARD_ITEM_H
