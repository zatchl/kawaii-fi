#ifndef ERP_INFO_STANDARD_ITEM_H
#define ERP_INFO_STANDARD_ITEM_H

#include <QStandardItem>

namespace KawaiiFi::Ies {
	class ErpInfo;
	class ErpInfoStandardItem : public QStandardItem {
	public:
		explicit ErpInfoStandardItem(const ErpInfo &erp_info);
	};
} // namespace KawaiiFi::Ies

#endif // ERP_INFO_STANDARD_ITEM_H
