#include "nl_wifi_scan.h"

#include "libkawaii-fi/access_point.h"
#include "nl_parse_attr.h"
#include "nl_wifi_command.h"

#include <QString>
#include <QVector>
#include <array>
#include <libnl3/netlink/attr.h>
#include <libnl3/netlink/genl/genl.h>
#include <libnl3/netlink/handlers.h>
#include <libnl3/netlink/msg.h>
#include <linux/netlink.h>
#include <linux/nl80211.h>

struct genlmsghdr;
struct nl_msg;

namespace KawaiiFi {
	namespace {
		std::array<nla_policy, NL80211_BSS_MAX + 1> bss_validation_policy()
		{
			std::array<nla_policy, NL80211_BSS_MAX + 1> policy{};
			policy[NL80211_BSS_TSF].type = NLA_U64;
			policy[NL80211_BSS_FREQUENCY].type = NLA_U32;
			policy[NL80211_BSS_BSSID] = {};
			policy[NL80211_BSS_BEACON_INTERVAL].type = NLA_U16;
			policy[NL80211_BSS_CAPABILITY].type = NLA_U16;
			policy[NL80211_BSS_INFORMATION_ELEMENTS] = {};
			policy[NL80211_BSS_SIGNAL_MBM].type = NLA_U32;
			policy[NL80211_BSS_SIGNAL_UNSPEC].type = NLA_U8;
			policy[NL80211_BSS_STATUS].type = NLA_U32;
			policy[NL80211_BSS_SEEN_MS_AGO].type = NLA_U32;
			policy[NL80211_BSS_BEACON_IES] = {};
			return policy;
		}

		int update_ap(nl_msg *msg, void *aps)
		{
			auto gnlh = static_cast<genlmsghdr *>(nlmsg_data(nlmsg_hdr(msg)));
			std::array<nlattr *, NL80211_ATTR_MAX + 1> attribute_index{};
			std::array<nlattr *, NL80211_BSS_MAX + 1> bss_attribute_index{};

			static std::array<nla_policy, NL80211_BSS_MAX + 1> bss_policy = bss_validation_policy();

			// Fill the attribute index
			nla_parse(attribute_index.begin(), NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0),
			          genlmsg_attrlen(gnlh, 0), nullptr);

			// Skip if there's no BSS attribute
			if (attribute_index[NL80211_ATTR_BSS] == nullptr) {
				return NL_SKIP;
			}

			// Create attribute index based on nested attribute
			if (nla_parse_nested(bss_attribute_index.begin(), NL80211_BSS_MAX,
			                     attribute_index[NL80211_ATTR_BSS], bss_policy.begin()) != 0) {
				return NL_SKIP;
			}

			if (bss_attribute_index[NL80211_BSS_BSSID] == nullptr) {
				return NL_SKIP;
			}

			auto access_points = static_cast<QVector<KawaiiFi::AccessPoint> *>(aps);
			if (access_points == nullptr) {
				return NL_SKIP;
			}

			const QString bss_bssid = parse_bssid(bss_attribute_index[NL80211_BSS_BSSID]);
			for (KawaiiFi::AccessPoint &ap : *access_points) {
				if (ap.bssid() == bss_bssid) {
					ap.update_data(bss_attribute_index);
					return NL_SKIP;
				}
			}

			access_points->append(KawaiiFi::AccessPoint(bss_bssid, bss_attribute_index));
			return NL_SKIP;
		}
	} // namespace

	bool update_aps_using_last_scan(QVector<KawaiiFi::AccessPoint> &aps, unsigned int if_index)
	{
		KawaiiFi::NlWifiCommand<QVector<KawaiiFi::AccessPoint>> command(
		        NL80211_CMD_GET_SCAN, NLM_F_DUMP, &update_ap, &aps);
		int result = command.send(if_index);
		return result == 0;
	}
} // namespace KawaiiFi
