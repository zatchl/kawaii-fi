#ifndef RSN_STANDARD_ITEM_H
#define RSN_STANDARD_ITEM_H

#include <QStandardItem>
#include <libkawaii-fi/ies/robust_security_network.h>

class RsnStandardItem : public QStandardItem {
public:
	RsnStandardItem(const RobustSecurityNetwork &rsn);
};

#endif // RSN_STANDARD_ITEM_H
