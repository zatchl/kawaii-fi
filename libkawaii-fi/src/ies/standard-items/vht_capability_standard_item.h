#ifndef VHT_CAPABILITY_STANDARD_ITEM_H
#define VHT_CAPABILITY_STANDARD_ITEM_H

#include <QStandardItem>

namespace KawaiiFi::Ies {
	class VhtCapabilities;
	class VhtCapabilityStandardItem : public QStandardItem {
	public:
		explicit VhtCapabilityStandardItem(const VhtCapabilities &vht_cap);
	};
} // namespace KawaiiFi::Ies

#endif // VHT_CAPABILITY_STANDARD_ITEM_H
