#ifndef EXTENDED_CAPABILITIES_H
#define EXTENDED_CAPABILITIES_H

#include "information_element.h"

class QStandardItem;

class ExtendedCapabilities : public InformationElement {
public:
	ExtendedCapabilities() = default;
	ExtendedCapabilities(const InformationElement &ie);

	[[nodiscard]] QStandardItem *standard_item() const override;

	[[nodiscard]] bool twenty_forty_bss_coexistence_management() const;
	[[nodiscard]] bool extended_channel_switching() const;
	[[nodiscard]] bool psmp_capability() const;
	[[nodiscard]] bool spsmp_support() const;
	[[nodiscard]] bool event() const;
	[[nodiscard]] bool diagnostics() const;
	[[nodiscard]] bool multicast_diagnostics() const;
	[[nodiscard]] bool location_tracking() const;
	[[nodiscard]] bool fms() const;
	[[nodiscard]] bool proxy_arp_service() const;
	[[nodiscard]] bool collocated_interference_reporting() const;
	[[nodiscard]] bool civic_location() const;
	[[nodiscard]] bool geospatial_location() const;
	[[nodiscard]] bool tfs() const;
	[[nodiscard]] bool wnm_sleep_mode() const;
	[[nodiscard]] bool tim_broadcast() const;
	[[nodiscard]] bool bss_transition() const;
	[[nodiscard]] bool qos_traffic_capability() const;
	[[nodiscard]] bool ac_station_count() const;
	[[nodiscard]] bool multiple_bssid() const;
	[[nodiscard]] bool timing_measurement() const;
	[[nodiscard]] bool channel_usage() const;
	[[nodiscard]] bool ssid_list() const;
	[[nodiscard]] bool dms() const;
	[[nodiscard]] bool utc_tsf_offset() const;
	[[nodiscard]] bool tpu_buffer_sta_support() const;
	[[nodiscard]] bool tdls_peer_psm_support() const;
	[[nodiscard]] bool tdls_channel_switching() const;
	[[nodiscard]] bool interworking() const;
	[[nodiscard]] bool qos_map() const;
	[[nodiscard]] bool ebr() const;
	[[nodiscard]] bool sspn_interface() const;
	[[nodiscard]] bool msgcf_capability() const;
	[[nodiscard]] bool tdls_support() const;
	[[nodiscard]] bool tdls_prohibited() const;
	[[nodiscard]] bool tdls_channel_switching_prohibited() const;
	[[nodiscard]] bool reject_unadmitted_frame() const;
	[[nodiscard]] unsigned int service_interval_granularity() const;
	[[nodiscard]] bool identifier_location() const;
	[[nodiscard]] bool uapsd_coexistence() const;
	[[nodiscard]] bool wnm_notification() const;
	[[nodiscard]] bool qab_capability() const;
	[[nodiscard]] bool utf8_ssid() const;
	[[nodiscard]] bool qmf_activated() const;
	[[nodiscard]] bool qmf_reconfiguration_activated() const;
	[[nodiscard]] bool robust_av_streaming() const;
	[[nodiscard]] bool advanced_gcr() const;
	[[nodiscard]] bool mesh_gcr() const;
	[[nodiscard]] bool scs() const;
	[[nodiscard]] bool qload_report() const;
	[[nodiscard]] bool alternate_edca() const;
	[[nodiscard]] bool unprotected_txop_negotiation() const;
	[[nodiscard]] bool protected_txop_negotiation() const;
	[[nodiscard]] bool protected_qload_report() const;
	[[nodiscard]] bool tdls_wider_bandwidth() const;
	[[nodiscard]] bool operating_mode_notification() const;
	[[nodiscard]] unsigned int max_msdus_in_amsdu() const;
};

inline const unsigned int WLAN_EID_EXT_CAPABILITY = 127;

#endif // EXTENDED_CAPABILITIES_H
