#include "vht_operation_standard_item.h"

#include <QStandardItem>
#include <QString>
#include <libkawaii-fi/ies/vht_operations.h>

VhtOperationStandardItem::VhtOperationStandardItem(const VhtOperations &vht_op)
    : QStandardItem("VHT Operation")
{
	switch (vht_op.channel_width()) {
	case VhtChannelWidth::TwentyOrFortyMhz:
		appendRow({new QStandardItem("Channel Width"), new QStandardItem("20 or 40 MHz")});
		break;
	case VhtChannelWidth::EightyMhz:
		appendRow({new QStandardItem("Channel Width"), new QStandardItem("80 MHz")});
		break;
	case VhtChannelWidth::OneSixtyMhz:
		appendRow({new QStandardItem("Channel Width"), new QStandardItem("160 MHz")});
		break;
	case VhtChannelWidth::EightyPlusEightyMhz:
		appendRow({new QStandardItem("Channel Width"), new QStandardItem("80+80 MHz")});
		break;
	}

	appendRow({new QStandardItem("Channel Center Segment 0"),
	           new QStandardItem(QString::number(vht_op.channel_center_segment_zero()))});

	appendRow({new QStandardItem("Channel Center Segment 1"),
	           new QStandardItem(QString::number(vht_op.channel_center_segment_one()))});
}
