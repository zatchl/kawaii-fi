#include "access_point_detail_tree.h"

#include "scanning/access_point_scanner.h"
#include "tree-items/country_info_standard_item.h"
#include "tree-items/erp_info_standard_item.h"
#include "tree-items/extended_capabilities_standard_item.h"
#include "tree-items/ht_capability_standard_item.h"
#include "tree-items/ht_operation_standard_item.h"
#include "tree-items/ie_id_standard_item.h"
#include "tree-items/ie_length_standard_item.h"
#include "tree-items/power_constraint_standard_item.h"
#include "tree-items/rm_capabilities_standard_item.h"
#include "tree-items/rsn_standard_item.h"
#include "tree-items/supported_rates_standard_item.h"
#include "tree-items/tim_standard_item.h"
#include "tree-items/vht_capability_standard_item.h"
#include "tree-items/vht_operation_standard_item.h"

#include <QByteArray>
#include <QHashNode>
#include <QHeaderView>
#include <QList>
#include <QStandardItem>
#include <QStringList>
#include <QTreeView>
#include <QVector>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/channel.h>
#include <libkawaii-fi/ies/country_info.h>
#include <libkawaii-fi/ies/ds_parameter.h>
#include <libkawaii-fi/ies/erp_info.h>
#include <libkawaii-fi/ies/extended_capabilities.h>
#include <libkawaii-fi/ies/ht_capabilities.h>
#include <libkawaii-fi/ies/ht_operations.h>
#include <libkawaii-fi/ies/information_element.h>
#include <libkawaii-fi/ies/power_constraint.h>
#include <libkawaii-fi/ies/rm_capabilities.h>
#include <libkawaii-fi/ies/robust_security_network.h>
#include <libkawaii-fi/ies/ssid.h>
#include <libkawaii-fi/ies/supported_rates.h>
#include <libkawaii-fi/ies/traffic_indication_map.h>
#include <libkawaii-fi/ies/vht_capabilities.h>
#include <libkawaii-fi/ies/vht_operations.h>

namespace {
	QList<QStandardItem *> ie_tree_row(QStandardItem *ie_standard_item, const QString &ie_data,
	                                   unsigned int ie_id, const QByteArray &bytes)
	{
		return {ie_standard_item, new QStandardItem(ie_data), new IeIdStandardItem(ie_id),
		        new IeLengthStandardItem(bytes.size()),
		        new QStandardItem(QString(bytes.toHex(' ').toUpper()))};
	}
} // namespace

AccessPointDetailTreeView::AccessPointDetailTreeView(QWidget *parent) : QTreeView(parent)
{
	header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	setModel(model_);
	model_->setHorizontalHeaderLabels({"Information Element", "Value", "ID", "Length", "Raw Data"});
}

void AccessPointDetailTreeView::show_ies(const QString &bssid)
{
	if (!ap_scanner_) {
		return;
	}

	// Clear the model
	model_->removeRows(0, model_->rowCount());

	// Find the access point with the given BSSID and display its IEs
	for (const auto &ap : ap_scanner_->access_points()) {
		if (ap.bssid() == bssid) {
			show_ies_for_ap(ap);
			break;
		}
	}
}

void AccessPointDetailTreeView::set_ap_scanner(const AccessPointScanner *ap_scanner)
{
	ap_scanner_ = ap_scanner;
}

void AccessPointDetailTreeView::show_ies_for_ap(const AccessPoint &ap)
{
	for (auto it = ap.information_elements().constBegin();
	     it != ap.information_elements().constEnd(); ++it) {
		switch (it.key()) {
		case WLAN_EID_SSID:
			model_->invisibleRootItem()->appendRow(ie_tree_row(
			        new QStandardItem("SSID"), it.value().bytes(), it.key(), it.value().bytes()));
			break;
		case WLAN_EID_SUPP_RATES:
		case WLAN_EID_EXT_SUPP_RATES: {
			SupportedRates supported_rates(it.value());
			model_->invisibleRootItem()->appendRow(ie_tree_row(
			        new SupportedRatesStandardItem(it.value(), it.key() == WLAN_EID_EXT_SUPP_RATES),
			        QString("%0 Mbps").arg(supported_rates.text_rates().join(", ")), it.key(),
			        it.value().bytes()));
			break;
		}
		case WLAN_EID_DS_PARAMS:
			model_->invisibleRootItem()->appendRow(
			        ie_tree_row(new QStandardItem("DS Parameter Set"),
			                    QString("Channel %0").arg(DsParameter(it.value()).channel()),
			                    it.key(), it.value().bytes()));
			break;
		case WLAN_EID_HT_CAPABILITY:
			model_->invisibleRootItem()->appendRow(ie_tree_row(
			        new HtCapabilityStandardItem(it.value()), "", it.key(), it.value().bytes()));
			break;
		case WLAN_EID_HT_OPERATION:
			model_->invisibleRootItem()->appendRow(ie_tree_row(
			        new HtOperationStandardItem(it.value()), "", it.key(), it.value().bytes()));
			break;
		case WLAN_EID_VHT_CAPABILITY:
			model_->invisibleRootItem()->appendRow(ie_tree_row(
			        new VhtCapabilityStandardItem(it.value()), "", it.key(), it.value().bytes()));
			break;
		case WLAN_EID_VHT_OPERATION:
			model_->invisibleRootItem()->appendRow(ie_tree_row(
			        new VhtOperationStandardItem(it.value()), "", it.key(), it.value().bytes()));
			break;
		case WLAN_EID_RSN:
			model_->invisibleRootItem()->appendRow(
			        ie_tree_row(new RsnStandardItem(it.value()), "", it.key(), it.value().bytes()));
			break;
		case WLAN_EID_PWR_CONSTRAINT: {
			const PowerConstraint power_constraint(it.value());
			model_->invisibleRootItem()->appendRow(
			        ie_tree_row(new PowerConstraintStandardItem(power_constraint),
			                    QString("%0 dB").arg(power_constraint.local_power_constraint()),
			                    it.key(), it.value().bytes()));
			break;
		}
		case WLAN_EID_COUNTRY: {
			const CountryInfo country_info(it.value());
			model_->invisibleRootItem()->appendRow(
			        ie_tree_row(new CountryInfoStandardItem(country_info, ap.channel().band()),
			                    country_info.country_code(), it.key(), it.value().bytes()));
			break;
		}
		case WLAN_EID_RRM_ENABLED_CAPABILITIES:
			model_->invisibleRootItem()->appendRow(ie_tree_row(
			        new RmCapabilitiesStandardItem(it.value()), "", it.key(), it.value().bytes()));
			break;
		case WLAN_EID_TIM:
			model_->invisibleRootItem()->appendRow(
			        ie_tree_row(new TimStandardItem(it.value()), "", it.key(), it.value().bytes()));
			break;
		case WLAN_EID_ERP_INFO:
			model_->invisibleRootItem()->appendRow(ie_tree_row(new ErpInfoStandardItem(it.value()),
			                                                   "", it.key(), it.value().bytes()));
			break;
		case WLAN_EID_EXT_CAPABILITY:
			model_->invisibleRootItem()->appendRow(
			        ie_tree_row(new ExtendedCapabilitiesStandardItem(it.value()), "", it.key(),
			                    it.value().bytes()));
			break;
		default:
			model_->invisibleRootItem()->appendRow(
			        ie_tree_row(new QStandardItem("Unknown"), "", it.key(), it.value().bytes()));
		}
	}
}
