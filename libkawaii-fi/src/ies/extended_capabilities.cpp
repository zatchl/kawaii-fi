#include "libkawaii-fi/ies/extended_capabilities.h"

#include "libkawaii-fi/ies/information_element.h"
#include "standard-items/extended_capabilities_standard_item.h"

ExtendedCapabilities::ExtendedCapabilities(const InformationElement &ie)
    : InformationElement(ie.bytes())
class QStandardItem;

QStandardItem *ExtendedCapabilities::standard_item() const
{
	return new ExtendedCapabilitiesStandardItem(*this);
}

bool ExtendedCapabilities::twenty_forty_bss_coexistence_management() const { return false; }

bool ExtendedCapabilities::extended_channel_switching() const { return false; }

bool ExtendedCapabilities::psmp_capability() const { return false; }

bool ExtendedCapabilities::spsmp_support() const { return false; }

bool ExtendedCapabilities::event() const { return false; }

bool ExtendedCapabilities::diagnostics() const { return false; }

bool ExtendedCapabilities::multicast_diagnostics() const { return false; }

bool ExtendedCapabilities::location_tracking() const { return false; }

bool ExtendedCapabilities::fms() const { return false; }

bool ExtendedCapabilities::proxy_arp_service() const { return false; }

bool ExtendedCapabilities::collocated_interference_reporting() const { return false; }

bool ExtendedCapabilities::civic_location() const { return false; }

bool ExtendedCapabilities::geospatial_location() const { return false; }

bool ExtendedCapabilities::tfs() const { return false; }

bool ExtendedCapabilities::wnm_sleep_mode() const { return false; }

bool ExtendedCapabilities::tim_broadcast() const { return false; }

bool ExtendedCapabilities::bss_transition() const { return false; }

bool ExtendedCapabilities::qos_traffic_capability() const { return false; }

bool ExtendedCapabilities::ac_station_count() const { return false; }

bool ExtendedCapabilities::multiple_bssid() const { return false; }

bool ExtendedCapabilities::timing_measurement() const { return false; }

bool ExtendedCapabilities::channel_usage() const { return false; }

bool ExtendedCapabilities::ssid_list() const { return false; }

bool ExtendedCapabilities::dms() const { return false; }

bool ExtendedCapabilities::utc_tsf_offset() const { return false; }

bool ExtendedCapabilities::tpu_buffer_sta_support() const { return false; }

bool ExtendedCapabilities::tdls_peer_psm_support() const { return false; }

bool ExtendedCapabilities::tdls_channel_switching() const { return false; }

bool ExtendedCapabilities::interworking() const { return false; }

bool ExtendedCapabilities::qos_map() const { return false; }

bool ExtendedCapabilities::ebr() const { return false; }

bool ExtendedCapabilities::sspn_interface() const { return false; }

bool ExtendedCapabilities::msgcf_capability() const { return false; }

bool ExtendedCapabilities::tdls_support() const { return false; }

bool ExtendedCapabilities::tdls_prohibited() const { return false; }

bool ExtendedCapabilities::tdls_channel_switching_prohibited() const { return false; }

bool ExtendedCapabilities::reject_unadmitted_frame() const { return false; }

unsigned int ExtendedCapabilities::service_interval_granularity() const { return 0; }

bool ExtendedCapabilities::identifier_location() const { return false; }

bool ExtendedCapabilities::uapsd_coexistence() const { return false; }

bool ExtendedCapabilities::wnm_notification() const { return false; }

bool ExtendedCapabilities::qab_capability() const { return false; }

bool ExtendedCapabilities::utf8_ssid() const { return false; }

bool ExtendedCapabilities::qmf_activated() const { return false; }

bool ExtendedCapabilities::qmf_reconfiguration_activated() const { return false; }

bool ExtendedCapabilities::robust_av_streaming() const { return false; }

bool ExtendedCapabilities::advanced_gcr() const { return false; }

bool ExtendedCapabilities::mesh_gcr() const { return false; }

bool ExtendedCapabilities::scs() const { return false; }

bool ExtendedCapabilities::qload_report() const { return false; }

bool ExtendedCapabilities::alternate_edca() const { return false; }

bool ExtendedCapabilities::unprotected_txop_negotiation() const { return false; }

bool ExtendedCapabilities::protected_txop_negotiation() const { return false; }

bool ExtendedCapabilities::protected_qload_report() const { return false; }

bool ExtendedCapabilities::tdls_wider_bandwidth() const { return false; }

bool ExtendedCapabilities::operating_mode_notification() const { return false; }

unsigned int ExtendedCapabilities::max_msdus_in_amsdu() const { return 0; }
