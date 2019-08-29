#include "ht_capability_standard_item.h"

#include <QStandardItem>
#include <QString>
#include <libkawaii-fi/ies/ht_capabilities.h>

HtCapabilityStandardItem::HtCapabilityStandardItem(const HtCapabilities &ht_cap)
    : QStandardItem("HT Capabilities")
{
	appendRow({new QStandardItem("LDPC Coding"),
	           new QStandardItem(ht_cap.ldpc_coding_capability() ? "Supported" : "Not Supported")});

	switch (ht_cap.supported_channel_width_set()) {
	case HtSupportedChannelWidth::TwentyMhz:
		appendRow({new QStandardItem("Supported Channel Width"), new QStandardItem("20 MHz")});
		break;
	case HtSupportedChannelWidth::TwentyOrFortyMhz:
		appendRow(
		        {new QStandardItem("Supported Channel Width"), new QStandardItem("20 or 40 MHz")});
		break;
	}

	switch (ht_cap.sm_power_save()) {
	case SmPowerSave::Disabled:
		appendRow({new QStandardItem("SM Power Save"), new QStandardItem("Disabled")});
		break;
	case SmPowerSave::Static:
		appendRow({new QStandardItem("SM Power Save"), new QStandardItem("Static")});
		break;
	case SmPowerSave::Dynamic:
		appendRow({new QStandardItem("SM Power Save"), new QStandardItem("Dynamic")});
		break;
	}

	appendRow({new QStandardItem("Greenfield PPDU"),
	           new QStandardItem(ht_cap.greenfield_ppdu() ? "Supported" : "Not Supported")});

	appendRow({new QStandardItem("Short GI (20 MHz)"),
	           new QStandardItem(ht_cap.short_gi_20_mhz() ? "Supported" : "Not Supported")});

	appendRow({new QStandardItem("Short GI (40 MHz)"),
	           new QStandardItem(ht_cap.short_gi_40_mhz() ? "Supported" : "Not Supported")});

	appendRow({new QStandardItem("Tx STBC"),
	           new QStandardItem(ht_cap.tx_stbc() ? "Supported" : "Not Supported")});

	switch (ht_cap.rx_stbc()) {
	case HtRxStbc::Disabled:
		appendRow({new QStandardItem("Rx STBC"), new QStandardItem("Not Supported")});
		break;
	case HtRxStbc::OneSpatialStream:
		appendRow({new QStandardItem("Rx STBC"), new QStandardItem("One Spatial Stream")});
		break;
	case HtRxStbc::TwoSpatialStreams:
		appendRow({new QStandardItem("Rx STBC"), new QStandardItem("Two Spatial Stream")});
		break;
	case HtRxStbc::ThreeSpatialStreams:
		appendRow({new QStandardItem("Rx STBC"), new QStandardItem("Three Spatial Stream")});
		break;
	}

	appendRow({new QStandardItem("Delayed Block ACK"),
	           new QStandardItem(ht_cap.delayed_block_ack() ? "Supported" : "Not Supported")});

	appendRow({new QStandardItem("Max A-MSDU Length"),
	           new QStandardItem(QString::number(ht_cap.max_amsdu_length()))});

	appendRow({new QStandardItem("DSSS/CCK Mode in 40 MHz"),
	           new QStandardItem(ht_cap.dsss_cck_40_mhz() ? "Supported" : "Not Supported")});

	appendRow({new QStandardItem("PSMP"),
	           new QStandardItem(ht_cap.psmp_support() ? "Supported" : "Not Supported")});

	appendRow({new QStandardItem("40 MHz Intolerant"),
	           new QStandardItem(ht_cap.forty_mhz_intolerant() ? "Yes" : "No")});

	appendRow({new QStandardItem("LSIG TXOP Protection"),
	           new QStandardItem(ht_cap.lsig_txop_protection() ? "Supported" : "Not Supported")});

	appendRow({new QStandardItem("Max A-MPDU Length"),
	           new QStandardItem(QString::number(ht_cap.max_ampdu_length()))});

	appendRow({new QStandardItem("MPDU Density"),
	           new QStandardItem(QString("%0 μs").arg(ht_cap.mpdu_density_usec()))});
}
