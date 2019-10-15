#include "ht_operation_standard_item.h"

#include <QStandardItem>
#include <QString>
#include <libkawaii-fi/ies/ht_operations.h>

namespace KawaiiFi::Ies {
	HtOperationStandardItem::HtOperationStandardItem(const HtOperations &ht_op)
	    : QStandardItem("HT Operation")
	{
		appendRow({new QStandardItem("Primary Channel"),
		           new QStandardItem(QString::number(ht_op.primary_channel()))});

		switch (ht_op.secondary_channel_offset()) {
		case SecondaryChannelOffset::Above:
			appendRow({new QStandardItem("Secondary Channel Offset"), new QStandardItem("Above")});
			break;
		case SecondaryChannelOffset::Below:
			appendRow({new QStandardItem("Secondary Channel Offset"), new QStandardItem("Below")});
			break;
		case SecondaryChannelOffset::NoSecondaryChannel:
			appendRow({new QStandardItem("Secondary Channel Offset"), new QStandardItem("None")});
			break;
		}

		appendRow({new QStandardItem("RIFS"),
		           new QStandardItem(ht_op.rifs() ? "Permitted" : "Prohibited")});

		switch (ht_op.ht_protection()) {
		case HtProtection::TwentyMhz:
			appendRow({new QStandardItem("HT Protection Mode"), new QStandardItem("HT 20 MHz")});
			break;
		case HtProtection::NonHtMixed:
			appendRow({new QStandardItem("HT Protection Mode"), new QStandardItem("Non-HT Mixed")});
			break;
		case HtProtection::Nonmember:
			appendRow({new QStandardItem("HT Protection Mode"), new QStandardItem("HT Nonmember")});
			break;
		case HtProtection::None:
			appendRow({new QStandardItem("HT Protection Mode"),
			           new QStandardItem("Greenfield (No Protection)")});
			break;
		}

		appendRow({new QStandardItem("Non Greenfield Stations"),
		           new QStandardItem(ht_op.non_greenfield_stas_present() ? "Present"
		                                                                 : "Not Present")});

		appendRow(
		        {new QStandardItem("OBSS Non HT Stations"),
		         new QStandardItem(ht_op.obss_non_ht_stas_present() ? "Present" : "Not Present")});

		appendRow({new QStandardItem("Center Frequency Segment 2"),
		           new QStandardItem(QString::number(ht_op.center_freq_segment_two()))});

		appendRow({new QStandardItem("Dual Beacon"),
		           new QStandardItem(ht_op.dual_beacon() ? "Yes" : "No")});

		appendRow({new QStandardItem("Dual CTS Protection"),
		           new QStandardItem(ht_op.dual_cts_protection() ? "Required" : "Not Required")});

		appendRow({new QStandardItem("STBC Beacon"), new QStandardItem("N/A")});

		appendRow({new QStandardItem("L-SIG TXOP Protection Full Support"),
		           new QStandardItem(ht_op.lsig_txop_protection_full_support() ? "Yes" : "No")});

		appendRow({new QStandardItem("PCO Active"),
		           new QStandardItem(ht_op.pco_active() ? "Yes" : "No")});

		if (ht_op.pco_active()) {
			switch (ht_op.pco_phase()) {
			case PcoPhase::TwentyMhz:
				appendRow({new QStandardItem("PCO Phase"), new QStandardItem("20 MHz")});
				break;
			case PcoPhase::FortyMhz:
				appendRow({new QStandardItem("PCO Phase"), new QStandardItem("40 MHz")});
				break;
			}
		} else {
			appendRow({new QStandardItem("PCO Phase"), new QStandardItem("N/A")});
		}
	}
} // namespace KawaiiFi::Ies
