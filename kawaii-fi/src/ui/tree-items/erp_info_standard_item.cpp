#include "erp_info_standard_item.h"

#include "affirmable_field_standard_item.h"

#include <libkawaii-fi/ies/erp_info.h>

ErpInfoStandardItem::ErpInfoStandardItem(const ErpInfo &erp_info) : QStandardItem("ERP Info")
{
	appendRow(affirmable_field_row("Non-ERP Present", erp_info.non_erp_present()));

	appendRow(affirmable_field_row("Use Protection", erp_info.use_protection()));

	appendRow(affirmable_field_row("Barker Preamble Mode", erp_info.barker_preamble_mode()));
}
