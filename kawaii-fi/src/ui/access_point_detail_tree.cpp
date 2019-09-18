#include "access_point_detail_tree.h"

#include "scanning/access_point_scanner.h"

#include <QByteArray>
#include <QHeaderView>
#include <QStandardItem>
#include <QTreeView>
#include <QVector>
#include <algorithm>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/ies/information_element.h>
#include <libkawaii-fi/ies/standard-items/ie_id_standard_item.h>
#include <libkawaii-fi/ies/standard-items/ie_length_standard_item.h>
#include <variant>

AccessPointDetailTreeView::AccessPointDetailTreeView(QWidget *parent) : QTreeView(parent)
{
	header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	setModel(model_);
	model_->setHorizontalHeaderLabels({"Information Element", "Value", "ID", "Length", "Bytes"});
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
	auto append_ie = [this](const InformationElement &ie) {
		model_->invisibleRootItem()->appendRow(
		        {ie.standard_item(), new QStandardItem(ie.summary()), new IeIdStandardItem(ie.id()),
		         new IeLengthStandardItem(ie.bytes().size()),
		         new QStandardItem(QString(ie.bytes().toHex(' ').toUpper()))});
	};
	for (const auto &ie_variant : ap.information_elements()) {
		std::visit(append_ie, ie_variant);
	}
}
