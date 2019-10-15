#include "extended_capabilities_standard_item.h"

#include "affirmable_field_standard_item.h"
#include "supportable_field_standard_item.h"

#include <QString>
#include <libkawaii-fi/ies/extended_capabilities.h>

namespace KawaiiFi::Ies {
	ExtendedCapabilitiesStandardItem::ExtendedCapabilitiesStandardItem(
	        const ExtendedCapabilities &extended_capabilities)
	    : QStandardItem("Extended Capabilities")
	{
		appendRow(supportable_field_row(
		        "20/40 BSS Coexistence Management",
		        extended_capabilities.twenty_forty_bss_coexistence_management()));

		appendRow(supportable_field_row("Extended Channel Switching",
		                                extended_capabilities.extended_channel_switching()));

		appendRow(
		        supportable_field_row("PSMP Capability", extended_capabilities.psmp_capability()));

		appendRow(supportable_field_row("S-PSMP", extended_capabilities.spsmp_support()));

		appendRow(supportable_field_row("Event", extended_capabilities.event()));

		appendRow(supportable_field_row("Diagnostics", extended_capabilities.diagnostics()));

		appendRow(supportable_field_row("Multicast Diagnostics",
		                                extended_capabilities.multicast_diagnostics()));

		appendRow(supportable_field_row("Location Tracking",
		                                extended_capabilities.location_tracking()));

		appendRow(supportable_field_row("FMS", extended_capabilities.fms()));

		appendRow(supportable_field_row("Proxy ARP Service",
		                                extended_capabilities.proxy_arp_service()));

		appendRow(supportable_field_row("Collocated Interference Reporting",
		                                extended_capabilities.collocated_interference_reporting()));

		appendRow(supportable_field_row("Civic Location", extended_capabilities.civic_location()));

		appendRow(supportable_field_row("Geospatial Location",
		                                extended_capabilities.geospatial_location()));

		appendRow(supportable_field_row("TFS", extended_capabilities.tfs()));

		appendRow(supportable_field_row("TIM Broadcast", extended_capabilities.tim_broadcast()));

		appendRow(supportable_field_row("BSS Transition", extended_capabilities.bss_transition()));

		appendRow(supportable_field_row("Qos Traffic Capability",
		                                extended_capabilities.qos_traffic_capability()));

		appendRow(supportable_field_row("AC Station Count",
		                                extended_capabilities.ac_station_count()));

		appendRow(supportable_field_row("Multiple BSSID", extended_capabilities.multiple_bssid()));

		appendRow(supportable_field_row("Timing Measurement",
		                                extended_capabilities.timing_measurement()));

		appendRow(supportable_field_row("Channel Usage", extended_capabilities.channel_usage()));

		appendRow(supportable_field_row("SSID List", extended_capabilities.ssid_list()));

		appendRow(supportable_field_row("DMS", extended_capabilities.dms()));

		appendRow(supportable_field_row("UTC TSF Offset", extended_capabilities.utc_tsf_offset()));

		appendRow(supportable_field_row("TPU Buffer STA",
		                                extended_capabilities.tpu_buffer_sta_support()));

		appendRow(supportable_field_row("TDLS Peer PSM",
		                                extended_capabilities.tdls_peer_psm_support()));

		appendRow(supportable_field_row("TDLS Channel Switching",
		                                extended_capabilities.tdls_channel_switching()));

		appendRow(supportable_field_row("Interworking", extended_capabilities.interworking()));

		appendRow(supportable_field_row("QoS Map", extended_capabilities.qos_map()));

		appendRow(supportable_field_row("EBR", extended_capabilities.ebr()));

		appendRow(supportable_field_row("SSPN Interface", extended_capabilities.sspn_interface()));

		appendRow(supportable_field_row("MSGCF Capability",
		                                extended_capabilities.msgcf_capability()));

		appendRow(supportable_field_row("TDLS Support", extended_capabilities.tdls_support()));

		appendRow(
		        supportable_field_row("TDLS Prohibited", extended_capabilities.tdls_prohibited()));

		appendRow(supportable_field_row("TDLS Channel Switching Prohibited",
		                                extended_capabilities.tdls_channel_switching_prohibited()));

		appendRow(supportable_field_row("Reject Unadmitted Frame",
		                                extended_capabilities.reject_unadmitted_frame()));

		appendRow({new QStandardItem("Service Interval Granularity"),
		           new QStandardItem(QString("%0 ms").arg(
		                   extended_capabilities.service_interval_granularity()))});

		appendRow(supportable_field_row("Identifier Location",
		                                extended_capabilities.identifier_location()));

		appendRow(supportable_field_row("U-APSD Coexistence",
		                                extended_capabilities.uapsd_coexistence()));

		appendRow(supportable_field_row("WNM Notification",
		                                extended_capabilities.wnm_notification()));

		appendRow(supportable_field_row("QAB Capability", extended_capabilities.qab_capability()));

		appendRow(supportable_field_row("UTF-8 SSID", extended_capabilities.utf8_ssid()));

		appendRow(affirmable_field_row("QMFActivated", extended_capabilities.qmf_activated()));

		appendRow(affirmable_field_row("QMFReconfigurationActivated",
		                               extended_capabilities.qmf_reconfiguration_activated()));

		appendRow(affirmable_field_row("Robust AV Streaming",
		                               extended_capabilities.robust_av_streaming()));

		appendRow(affirmable_field_row("Advanced GCR", extended_capabilities.advanced_gcr()));

		appendRow(affirmable_field_row("Mesh GCR", extended_capabilities.mesh_gcr()));

		appendRow(affirmable_field_row("SCS", extended_capabilities.scs()));

		appendRow(affirmable_field_row("QLoad Report", extended_capabilities.qload_report()));

		appendRow(affirmable_field_row("Alternate EDCA", extended_capabilities.alternate_edca()));

		appendRow(affirmable_field_row("Unprotected TXOP Negotiation",
		                               extended_capabilities.unprotected_txop_negotiation()));

		appendRow(affirmable_field_row("Protected TXOP Negotiation",
		                               extended_capabilities.protected_txop_negotiation()));

		appendRow(affirmable_field_row("Protected QLoad Report",
		                               extended_capabilities.protected_qload_report()));

		appendRow(supportable_field_row("TDLS Wider Bandwidth",
		                                extended_capabilities.tdls_wider_bandwidth()));

		appendRow(supportable_field_row("Operating Mode Notification",
		                                extended_capabilities.operating_mode_notification()));

		appendRow({new QStandardItem("Max Number of MSDUs in A-MSDU"),
		           new QStandardItem(QString::number(extended_capabilities.max_msdus_in_amsdu()))});
	}
} // namespace KawaiiFi::Ies
