#include "nl_wifi_scan.h"

#include "nl_wifi_command.h"
#include "nl_wifi_parse.h"

#include <QString>
#include <QVector>
#include <chrono>
#include <libkawaii-fi/access_point.h>
#include <libnl3/netlink/genl/ctrl.h>
#include <libnl3/netlink/genl/genl.h>
#include <libnl3/netlink/handlers.h>
#include <linux/nl80211.h>

namespace {
	int process_access_point(nl_msg *msg, void *aps)
	{
		QVector<AccessPoint> *accessPoints = static_cast<QVector<AccessPoint> *>(aps);
		AccessPoint ap;

		genlmsghdr *gnlh = static_cast<genlmsghdr *>(nlmsg_data(nlmsg_hdr(msg)));
		nlattr *tb[NL80211_ATTR_MAX + 1];
		nlattr *bss[NL80211_BSS_MAX + 1];
		static nla_policy bss_policy[NL80211_BSS_MAX + 1];
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
		nla_parse(tb, NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0), genlmsg_attrlen(gnlh, 0),
		          nullptr);

		if (!tb[NL80211_ATTR_BSS]) {
			return NL_SKIP;
		}

		// Create attribute index based on nested attribute
		if (nla_parse_nested(bss, NL80211_BSS_MAX, tb[NL80211_ATTR_BSS], bss_policy)) {
			return NL_SKIP;
		}

		if (!bss[NL80211_BSS_BSSID]) {
			return NL_SKIP;
		}

		ap.bssid = KawaiiFi::parse_bssid(bss[NL80211_BSS_BSSID]);

		if (bss[NL80211_BSS_FREQUENCY]) {
			ap.frequency = KawaiiFi::parse_frequency(bss[NL80211_BSS_FREQUENCY]);
		}

		if (bss[NL80211_BSS_CHAN_WIDTH]) {
			ap.channelWidth = KawaiiFi::parse_channel_width(bss[NL80211_BSS_CHAN_WIDTH]);
		}

		if (bss[NL80211_BSS_INFORMATION_ELEMENTS]) {
			KawaiiFi::InformationElements ie =
			        KawaiiFi::parse_information_elements(bss[NL80211_BSS_INFORMATION_ELEMENTS]);
			ap.ssid = ie.ssid;
			ap.vendor = ie.vendor;
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
		genlmsghdr *gnlh = static_cast<genlmsghdr *>(nlmsg_data(nlmsg_hdr(msg)));
		int *callback_arg = static_cast<int *>(arg);

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
	nl_cb_set(callback, NL_CB_ACK, NL_CB_CUSTOM, [](nl_msg *msg, void *arg) -> int {
		int *callback_arg = static_cast<int *>(arg);
		*callback_arg = 0;
		return NL_STOP;
	}, &callback_arg);

	// Override Netlink's sequence number checking
	nl_cb_set(callback, NL_CB_SEQ_CHECK, NL_CB_CUSTOM, [](nl_msg *msg, void *arg) -> int {
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
