#include "erp_info_standard_item.h"

#include "affirmable_field_standard_item.h"

#include <initializer_list>
#include <libkawaii-fi/ies/erp_info.h>

namespace KawaiiFi::Ies {
	ErpInfoStandardItem::ErpInfoStandardItem(const ErpInfo &erp_info) : QStandardItem("ERP Info")
	{
		for (const auto &row :
		     {affirmable_field_row("Non-ERP Present", erp_info.non_erp_present()),
		      affirmable_field_row("Use Protection", erp_info.use_protection()),
		      affirmable_field_row("Barker Preamble Mode", erp_info.barker_preamble_mode())}) {
			appendRow(row);
		}
	}
} // namespace KawaiiFi::Ies
