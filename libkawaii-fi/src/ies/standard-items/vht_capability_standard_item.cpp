#include "vht_capability_standard_item.h"

#include <QStandardItem>
#include <QString>
#include <array>
#include <libkawaii-fi/ies/vht_capabilities.h>

namespace KawaiiFi::Ies {
	VhtCapabilityStandardItem::VhtCapabilityStandardItem(const VhtCapabilities &vht_cap)
	    : QStandardItem("VHT Capabilities")
	{
		appendRow({new QStandardItem("Max MPDU Length"),
		           new QStandardItem(QString("%0 bytes").arg(vht_cap.max_mpdu_length()))});

		switch (vht_cap.supported_channel_width_set()) {
		case VhtSupportedChannelWidth::NoOneSixtyMhzNoEightyPlusEightyMhz:
			appendRow({new QStandardItem("Supported Channel Widths"),
			           new QStandardItem("20, 40, or 80 MHz")});
			break;
		case VhtSupportedChannelWidth::OneSixtyMhz:
			appendRow({new QStandardItem("Supported Channel Widths"),
			           new QStandardItem("20, 40, 80, or 160 MHz")});
			break;
		case VhtSupportedChannelWidth::OneSixtyMhzEightyPlusEightyMhz:
			appendRow({new QStandardItem("Supported Channel Widths"),
			           new QStandardItem("20, 40, 80, 160, or 80+80 MHz")});
			break;
		}

		appendRow({new QStandardItem("RX LDPC Packets"),
		           new QStandardItem(vht_cap.rx_ldpc() ? "Supported" : "Not Supported")});

		appendRow({new QStandardItem("Short GI (80 MHz)"),
		           new QStandardItem(vht_cap.short_gi_80_mhz() ? "Supported" : "Not Supported")});

		appendRow({new QStandardItem("Short GI (160 MHz)"),
		           new QStandardItem(vht_cap.short_gi_160_mhz() ? "Supported" : "Not Supported")});

		appendRow({new QStandardItem("TX STBC"),
		           new QStandardItem(vht_cap.tx_stbc() ? "Supported" : "Not Supported")});

		switch (vht_cap.rx_stbc()) {
		case VhtRxStbc::NotSupported:
			appendRow({new QStandardItem("RX STBC"), new QStandardItem("Not Supported")});
			break;
		case VhtRxStbc::OneSpatialStream:
			appendRow({new QStandardItem("RX STBC"),
			           new QStandardItem("1 Spatial Stream Supported")});
			break;
		case VhtRxStbc::TwoSpatialStreams:
			appendRow({new QStandardItem("RX STBC"),
			           new QStandardItem("2 Spatial Streams Supported")});
			break;
		case VhtRxStbc::ThreeSpatialStreams:
			appendRow({new QStandardItem("RX STBC"),
			           new QStandardItem("3 Spatial Streams Supported")});
			break;
		case VhtRxStbc::FourSpatialStreams:
			appendRow({new QStandardItem("RX STBC"),
			           new QStandardItem("4 Spatial Streams Supported")});
			break;
		}

		appendRow({new QStandardItem("SU Beamformer Capable"),
		           new QStandardItem(vht_cap.su_beamformer_capable() ? "Yes" : "No")});

		appendRow({new QStandardItem("SU Beamformee Capable"),
		           new QStandardItem(vht_cap.su_beamformee_capable() ? "Yes" : "No")});

		appendRow({new QStandardItem("Beamformee STS Capability"),
		           new QStandardItem(QString::number(vht_cap.beamformee_sts()))});

		appendRow({new QStandardItem("Sounding Dimensions"),
		           new QStandardItem(QString::number(vht_cap.sounding_dimensions()))});

		appendRow({new QStandardItem("MU Beamformer Capable"),
		           new QStandardItem(vht_cap.mu_beamformer_capable() ? "Yes" : "No")});

		appendRow({new QStandardItem("MU Beamformee Capable"),
		           new QStandardItem(vht_cap.mu_beamformee_capable() ? "Yes" : "No")});

		appendRow({new QStandardItem("TXOP Power Save"),
		           new QStandardItem(vht_cap.vht_txop_ps() ? "Supported" : "Not Supported")});

		appendRow({new QStandardItem("+HTC VHT Capable"),
		           new QStandardItem(vht_cap.htc_vht_capable() ? "Yes" : "No")});

		appendRow({new QStandardItem("Max A-MPDU Length"),
		           new QStandardItem(QString("%0 bytes").arg(vht_cap.max_ampdu_length()))});

		switch (vht_cap.link_adaptation()) {
		case LinkAdaptation::NotSupported:
			appendRow({new QStandardItem("Link Adaptation"), new QStandardItem("Not Supported")});
			break;
		case LinkAdaptation::SupportedUnsolicited:
			appendRow(
			        {new QStandardItem("Link Adaptation"), new QStandardItem("Unsolicited Only")});
			break;
		case LinkAdaptation::SupportedResponseUnsolicited:
			appendRow({new QStandardItem("Link Adaptation"),
			           new QStandardItem("Response and Unsolicited")});
			break;
		}

		appendRow({new QStandardItem("Rx Antenna Pattern Consistency"),
		           new QStandardItem(vht_cap.rx_antenna_pattern_consistent() ? "Supported"
		                                                                     : "Not Supported")});

		appendRow({new QStandardItem("Tx Antenna Pattern Consistency"),
		           new QStandardItem(vht_cap.tx_antenna_pattern_consistent() ? "Supported"
		                                                                     : "Not Supported")});

		auto *rx_mcs_map = new QStandardItem("Rx MCS Map");
		std::array<VhtMcs, 8> mcs_rx = vht_cap.mcs_rx();
		for (unsigned long i = 0; i < mcs_rx.size(); ++i) {
			switch (mcs_rx[i]) {
			case VhtMcs::NotSupported:
				rx_mcs_map->appendRow(
				        {new QStandardItem(QString("%0 Spatial Stream(s)").arg(i + 1)),
				         new QStandardItem("Not Supported")});
				break;
			case VhtMcs::OneThroughSeven:
				rx_mcs_map->appendRow(
				        {new QStandardItem(QString("%0 Spatial Stream(s)").arg(i + 1)),
				         new QStandardItem("MCS 0-7")});
				break;
			case VhtMcs::OneThroughEight:
				rx_mcs_map->appendRow(
				        {new QStandardItem(QString("%0 Spatial Stream(s)").arg(i + 1)),
				         new QStandardItem("MCS 0-8")});
				break;
			case VhtMcs::OneThroughNine:
				rx_mcs_map->appendRow(
				        {new QStandardItem(QString("%0 Spatial Stream(s)").arg(i + 1)),
				         new QStandardItem("MCS 0-9")});
				break;
			}
		}
		appendRow(rx_mcs_map);

		auto *tx_mcs_map = new QStandardItem("Tx MCS Map");
		std::array<VhtMcs, 8> mcs_tx = vht_cap.mcs_tx();
		for (unsigned long i = 0; i < mcs_rx.size(); ++i) {
			switch (mcs_tx[i]) {
			case VhtMcs::NotSupported:
				tx_mcs_map->appendRow(
				        {new QStandardItem(QString("%0 Spatial Stream(s)").arg(i + 1)),
				         new QStandardItem("Not Supported")});
				break;
			case VhtMcs::OneThroughSeven:
				tx_mcs_map->appendRow(
				        {new QStandardItem(QString("%0 Spatial Stream(s)").arg(i + 1)),
				         new QStandardItem("MCS 0-7")});
				break;
			case VhtMcs::OneThroughEight:
				tx_mcs_map->appendRow(
				        {new QStandardItem(QString("%0 Spatial Stream(s)").arg(i + 1)),
				         new QStandardItem("MCS 0-8")});
				break;
			case VhtMcs::OneThroughNine:
				tx_mcs_map->appendRow(
				        {new QStandardItem(QString("%0 Spatial Stream(s)").arg(i + 1)),
				         new QStandardItem("MCS 0-9")});
				break;
			}
		}
		appendRow(tx_mcs_map);
	}
} // namespace KawaiiFi::Ies
