#ifndef RM_CAPABILITIES_STANDARD_ITEM_H
#define RM_CAPABILITIES_STANDARD_ITEM_H

#include <QStandardItem>

namespace KawaiiFi::Ies {
	class RmCapabilities;
	class RmCapabilitiesStandardItem : public QStandardItem {
	public:
		explicit RmCapabilitiesStandardItem(const RmCapabilities &rm_capabilities);
	};
} // namespace KawaiiFi::Ies

#endif // RM_CAPABILITIES_STANDARD_ITEM_H
