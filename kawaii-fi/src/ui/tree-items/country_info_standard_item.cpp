#include "country_info_standard_item.h"

#include <QString>
#include <QVector>
#include <libkawaii-fi/channel.h>
#include <libkawaii-fi/ies/country_info.h>

namespace {
	QString constraint_text(const ChannelPowerConstraint &constraint,
	                        unsigned int channel_number_delta)
	{
		if (constraint.number_of_channels > 1) {
			const unsigned int last_channel =
			        constraint.first_channel_number +
			        (constraint.number_of_channels - 1) * channel_number_delta;
			return QString("Channels %0-%1 @ %2 dBm")
			        .arg(constraint.first_channel_number)
			        .arg(last_channel)
			        .arg(constraint.max_transmit_power_dbm);
		}
		return QString("Channel %0 @ %1 dBm")
		        .arg(constraint.first_channel_number)
		        .arg(constraint.max_transmit_power_dbm);
	}
} // namespace

CountryInfoStandardItem::CountryInfoStandardItem(const CountryInfo &country_info,
                                                 WifiBand wifi_band)
    : QStandardItem("Country Info")
{
	appendRow({new QStandardItem("Country Code"), new QStandardItem(country_info.country_code())});

	switch (country_info.environment()) {
	case Environment::Any:
		appendRow({new QStandardItem("Environment"), new QStandardItem("Any")});
		break;
	case Environment::Indoor:
		appendRow({new QStandardItem("Environment"), new QStandardItem("Indoor")});
		break;
	case Environment::Outdoor:
		appendRow({new QStandardItem("Environment"), new QStandardItem("Outdoor")});
		break;
	}

	const unsigned int channel_number_delta = (wifi_band == WifiBand::TwoPointFourGhz) ? 1 : 4;
	for (auto &constraint : country_info.channel_constraints()) {
		QStandardItem *country_info_item = new QStandardItem("Country Info");
		country_info_item->appendRow(
		        {new QStandardItem("First Channel"),
		         new QStandardItem(QString::number(constraint.first_channel_number))});
		country_info_item->appendRow(
		        {new QStandardItem("Number of Channels"),
		         new QStandardItem(QString::number(constraint.number_of_channels))});
		country_info_item->appendRow(
		        {new QStandardItem("Maximum Transmit Power"),
		         new QStandardItem(QString("%0 dBm").arg(constraint.max_transmit_power_dbm))});
		appendRow({country_info_item,
		           new QStandardItem(constraint_text(constraint, channel_number_delta))});
	}
}
