#ifndef HT_CAPABILITY_STANDARD_ITEM_H
#define HT_CAPABILITY_STANDARD_ITEM_H

#include <QStandardItem>

namespace KawaiiFi::Ies {
	class HtCapabilities;
	class HtCapabilityStandardItem : public QStandardItem {
	public:
		explicit HtCapabilityStandardItem(const HtCapabilities &ht_cap);
	};
} // namespace KawaiiFi::Ies

#endif // HT_CAPABILITY_STANDARD_ITEM_H
