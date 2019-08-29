#ifndef ERP_INFO_STANDARD_ITEM_H
#define ERP_INFO_STANDARD_ITEM_H

#include <QStandardItem>
#include <libkawaii-fi/ies/erp_info.h>

class ErpInfoStandardItem : public QStandardItem {
public:
	ErpInfoStandardItem(const ErpInfo &erp_info);
};

#endif // ERP_INFO_STANDARD_ITEM_H
