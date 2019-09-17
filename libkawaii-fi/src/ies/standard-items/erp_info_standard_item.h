#ifndef ERP_INFO_STANDARD_ITEM_H
#define ERP_INFO_STANDARD_ITEM_H

#include <QStandardItem>

class ErpInfo;

class ErpInfoStandardItem : public QStandardItem {
public:
	explicit ErpInfoStandardItem(const ErpInfo &erp_info);
};

#endif // ERP_INFO_STANDARD_ITEM_H
