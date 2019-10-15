#include "country_info_standard_item.h"

#include <QString>
#include <QVector>
#include <libkawaii-fi/ies/country_info.h>

namespace KawaiiFi::Ies {
	CountryInfoStandardItem::CountryInfoStandardItem(const CountryInfo &country_info)
	    : QStandardItem("Country Info")
	{
		appendRow({new QStandardItem("Country Code"),
		           new QStandardItem(country_info.country_code())});

		switch (country_info.environment()) {
		case CountryInfo::Environment::Any:
			appendRow({new QStandardItem("Environment"), new QStandardItem("Any")});
			break;
		case CountryInfo::Environment::Indoor:
			appendRow({new QStandardItem("Environment"), new QStandardItem("Indoor")});
			break;
		case CountryInfo::Environment::Outdoor:
			appendRow({new QStandardItem("Environment"), new QStandardItem("Outdoor")});
			break;
		}

		for (auto &constraint : country_info.channel_constraints()) {
			auto *constraint_item = new QStandardItem("Country Info");
			constraint_item->appendRow(
			        {new QStandardItem("First Channel"),
			         new QStandardItem(QString::number(constraint.first_channel_number))});
			constraint_item->appendRow(
			        {new QStandardItem("Number of Channels"),
			         new QStandardItem(QString::number(constraint.number_of_channels))});
			constraint_item->appendRow(
			        {new QStandardItem("Max Transmit Power"),
			         new QStandardItem(QString("%0 dBm").arg(constraint.max_transmit_power_dbm))});
			if (constraint.number_of_channels > 1) {
				appendRow({constraint_item,
				           new QStandardItem(QString("Channels %0-%1 @ %2 dBm")
				                                     .arg(constraint.first_channel_number)
				                                     .arg(constraint.last_channel_number)
				                                     .arg(constraint.max_transmit_power_dbm))});
			} else {
				appendRow({constraint_item,
				           new QStandardItem(QString("Channel %0 @ %1 dBm")
				                                     .arg(constraint.first_channel_number)
				                                     .arg(constraint.max_transmit_power_dbm))});
			}
		}
	}
} // namespace KawaiiFi::Ies
