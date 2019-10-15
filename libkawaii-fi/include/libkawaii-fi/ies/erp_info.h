#ifndef ERP_INFO_H
#define ERP_INFO_H

#include "information_element.h"

#include <string_view>

class QStandardItem;

namespace KawaiiFi::Ies {
	class ErpInfo : public InformationElement {
	public:
		ErpInfo() = default;
		explicit ErpInfo(const std::string_view &bytes);

		[[nodiscard]] QStandardItem *standard_item() const override;

		[[nodiscard]] bool non_erp_present() const;
		[[nodiscard]] bool use_protection() const;
		[[nodiscard]] bool barker_preamble_mode() const;
	};

	inline const unsigned int WLAN_EID_ERP_INFO = 42;
} // namespace KawaiiFi::Ies

#endif // ERP_INFO_H
