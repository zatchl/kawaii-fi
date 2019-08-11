#include "nl_wifi_scan.h"

#include "libkawaii-fi/ies/ht_capabilities.h"
#include "libkawaii-fi/ies/supported_rates.h"
#include "libkawaii-fi/ies/vht_capabilities.h"
#include "nl_wifi_command.h"
#include "nl_wifi_parse.h"

#include <QHashNode>
#include <QSet>
#include <QVector>
#include <array>
#include <chrono>
#include <libkawaii-fi/access_point.h>
#include <libnl3/netlink/attr.h>
#include <libnl3/netlink/genl/ctrl.h>
#include <libnl3/netlink/genl/genl.h>
#include <libnl3/netlink/handlers.h>
#include <libnl3/netlink/msg.h>
#include <libnl3/netlink/netlink.h>
#include <libnl3/netlink/socket.h>
#include <linux/genetlink.h>
#include <linux/netlink.h>
#include <linux/nl80211.h>

struct nl_cb;
struct nl_msg;
struct nl_sock;

namespace {
	const int max_two_point_four_ghz_freq_mhz = 2500;

	int process_access_point(nl_msg *msg, void *aps)
	{
		auto accessPoints = static_cast<QVector<AccessPoint> *>(aps);
		AccessPoint ap;

		auto gnlh = static_cast<genlmsghdr *>(nlmsg_data(nlmsg_hdr(msg)));
		std::array<nlattr *, NL80211_ATTR_MAX + 1> tb{};
		std::array<nlattr *, NL80211_BSS_MAX + 1> bss{};
		static std::array<nla_policy, NL80211_BSS_MAX + 1> bss_policy;
		bss_policy[NL80211_BSS_TSF].type = NLA_U64;
		bss_policy[NL80211_BSS_FREQUENCY].type = NLA_U32;
		bss_policy[NL80211_BSS_BSSID] = {};
		bss_policy[NL80211_BSS_BEACON_INTERVAL].type = NLA_U16;
		bss_policy[NL80211_BSS_CAPABILITY].type = NLA_U16;
		bss_policy[NL80211_BSS_INFORMATION_ELEMENTS] = {};
		bss_policy[NL80211_BSS_SIGNAL_MBM].type = NLA_U32;
		bss_policy[NL80211_BSS_SIGNAL_UNSPEC].type = NLA_U8;
		bss_policy[NL80211_BSS_STATUS].type = NLA_U32;
		bss_policy[NL80211_BSS_SEEN_MS_AGO].type = NLA_U32;
		bss_policy[NL80211_BSS_BEACON_IES] = {};

		// Create attribute index
		nla_parse(tb.begin(), NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0), genlmsg_attrlen(gnlh, 0),
		          nullptr);

		if (!tb[NL80211_ATTR_BSS]) {
			return NL_SKIP;
		}

		// Create attribute index based on nested attribute
		if (nla_parse_nested(bss.begin(), NL80211_BSS_MAX, tb[NL80211_ATTR_BSS],
		                     bss_policy.begin())) {
			return NL_SKIP;
		}

		if (!bss[NL80211_BSS_BSSID]) {
			return NL_SKIP;
		}

		ap.set_bssid(KawaiiFi::parse_bssid(bss[NL80211_BSS_BSSID]));

		if (bss[NL80211_BSS_STATUS]) {
			ap.set_connection_status(KawaiiFi::parse_status(bss[NL80211_BSS_STATUS]));
		}

		if (bss[NL80211_BSS_SIGNAL_MBM]) {
			ap.set_signal_strength_mbm(
			        KawaiiFi::parse_signal_strength_mbm(bss[NL80211_BSS_SIGNAL_MBM]));
		}

		if (bss[NL80211_BSS_FREQUENCY]) {
			ap.set_frequency(KawaiiFi::parse_frequency(bss[NL80211_BSS_FREQUENCY]));
		}

		if (bss[NL80211_BSS_SEEN_MS_AGO]) {
			ap.set_age_ms(KawaiiFi::parse_age_ms(bss[NL80211_BSS_SEEN_MS_AGO]));
		}

		if (bss[NL80211_BSS_CAPABILITY]) {
			ap.set_capabilities(nla_get_string(bss[NL80211_BSS_CAPABILITY]),
			                    nla_len(bss[NL80211_BSS_CAPABILITY]));
		}

		if (bss[NL80211_BSS_INFORMATION_ELEMENTS]) {
			KawaiiFi::parse_information_elements(bss[NL80211_BSS_INFORMATION_ELEMENTS],
			                                     ap.information_elements());
		}

		static const std::array<double, 4> b_data_rates = {1, 2, 5.5, 11};
		static const std::array<double, 8> g_data_rates = {6, 9, 12, 18, 24, 36, 48, 54};
		static const std::array<double, 3> a_data_rates = {6, 12, 24};

		QSet<double> supported_rates =
		        SupportedRates(ap.information_elements().value(WLAN_EID_SUPP_RATES)).rates();
		supported_rates.unite(
		        SupportedRates(ap.information_elements().value(WLAN_EID_EXT_SUPP_RATES)).rates());

		if (ap.frequency() < max_two_point_four_ghz_freq_mhz) {
			for (const auto rate : b_data_rates) {
				if (supported_rates.contains(rate)) {
					ap.protocols().append(Protocol::B);
					break;
				}
			}
			for (const auto rate : g_data_rates) {
				if (supported_rates.contains(rate)) {
					ap.protocols().append(Protocol::G);
					break;
				}
			}
			if (ap.information_elements().contains(WLAN_EID_HT_CAPABILITY)) {
				ap.protocols().append(Protocol::N);
			}
		} else {
			for (const auto rate : a_data_rates) {
				if (supported_rates.contains(rate)) {
					ap.protocols().append(Protocol::A);
					break;
				}
			}
			if (ap.information_elements().contains(WLAN_EID_HT_CAPABILITY)) {
				ap.protocols().append(Protocol::N);
			}
			if (ap.information_elements().contains(WLAN_EID_VHT_CAPABILITY)) {
				ap.protocols().append(Protocol::AC);
			}
		}

		accessPoints->push_back(ap);
		return NL_SKIP;
	}
} // namespace

int KawaiiFi::trigger_scan_with_interface(unsigned int interface_index)
{
	NlWifiCommand trigger_scan_command(NL80211_CMD_TRIGGER_SCAN);
	return trigger_scan_command.send(interface_index);
}

int KawaiiFi::wait_for_new_wifi_scan_results(unsigned int timeout_seconds)
{
	nl_sock *socket = nl_socket_alloc();
	genl_connect(socket);
	// Resolve the Netlink family and group name to its identifier
	int multicast_id = genl_ctrl_resolve_grp(socket, "nl80211", "scan");
	// Join the multicast group specified by multicast_id
	if (nl_socket_add_memberships(socket, multicast_id, 0)) {
		nl_socket_free(socket);
		return -1;
	}

	int callback_arg = 1;
	nl_cb *callback = nl_cb_alloc(NL_CB_DEFAULT);

	// clang-format off
	// Set up a callback for when a valid message is received
	nl_cb_set(callback, NL_CB_VALID, NL_CB_CUSTOM, [](nl_msg *msg, void *arg) -> int {
		auto gnlh = static_cast<genlmsghdr *>(nlmsg_data(nlmsg_hdr(msg)));
		auto callback_arg = static_cast<int *>(arg);

		switch (gnlh->cmd) {
		// If the command from the recieved message indicates there are new scan results,
		// set the callback argument to 0 so we stop waiting for new messages
		case NL80211_CMD_NEW_SCAN_RESULTS:
			*callback_arg = 0;
			break;
		// If the command indicates the scan was aborted, set the callback argument to -1 to stop
		// waiting for new messages and to indicate there are no new scan results
		case NL80211_CMD_SCAN_ABORTED:
			*callback_arg = -1;
			break;
		}

		return NL_SKIP;
	}, &callback_arg);

	// Set up a callback for when ACKs are received
	nl_cb_set(callback, NL_CB_ACK, NL_CB_CUSTOM, [](nl_msg *, void *arg) -> int {
		auto callback_arg = static_cast<int *>(arg);
		*callback_arg = 0;
		return NL_STOP;
	}, &callback_arg);

	// Override Netlink's sequence number checking
	nl_cb_set(callback, NL_CB_SEQ_CHECK, NL_CB_CUSTOM, [](nl_msg *, void *) -> int {
		return NL_OK;
	}, nullptr);
	// clang-format on

	std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point timeout_time =
	        start_time + std::chrono::seconds(timeout_seconds);

	// Continue to listen for messages until the callback argument is less than 1 or the timeout is
	// reached
	while (callback_arg > 0) {
		nl_recvmsgs(socket, callback);

		if (timeout_seconds > 0 && std::chrono::steady_clock::now() > timeout_time) {
			callback_arg = -1;
			break;
		}
	}

	nl_cb_put(callback);
	nl_socket_free(socket);
	return callback_arg;
}

int KawaiiFi::get_wifi_scan_results(unsigned int interface_index, QVector<AccessPoint> &aps)
{
	NlWifiCommand<QVector<AccessPoint>> get_scan_results_command(NL80211_CMD_GET_SCAN, NLM_F_DUMP,
	                                                             &process_access_point, &aps);
	return get_scan_results_command.send(interface_index);
}
