#ifndef NL_WIFI_COMMAND_H
#define NL_WIFI_COMMAND_H

#include <libnl3/netlink/attr.h>
#include <libnl3/netlink/genl/ctrl.h>
#include <libnl3/netlink/genl/genl.h>
#include <libnl3/netlink/handlers.h>
#include <libnl3/netlink/msg.h>
#include <libnl3/netlink/netlink.h>
#include <libnl3/netlink/socket.h>
#include <linux/nl80211.h>

namespace KawaiiFi {
	template <typename T = void>
	class NlWifiCommand {
	public:
		explicit NlWifiCommand(nl80211_commands command, int flags = 0,
		                       nl_recvmsg_msg_cb_t valid_handler = nullptr,
		                       T *valid_handler_args = nullptr);
		NlWifiCommand(const NlWifiCommand &wifi_command) = delete;
		NlWifiCommand &operator=(const NlWifiCommand &wifi_command) = delete;
		NlWifiCommand(NlWifiCommand &&wifi_command) = delete;
		NlWifiCommand &operator=(NlWifiCommand &&wifi_command) = delete;
		~NlWifiCommand();
		int send(unsigned int interface_index);

	private:
		const nl80211_commands command_;
		const int flags_;
		nl_sock *socket_ = nullptr;
		nl_recvmsg_msg_cb_t valid_handler_ = nullptr;
		T *valid_handler_args_ = nullptr;
	};

	template <typename T>
	NlWifiCommand<T>::NlWifiCommand(nl80211_commands command, int flags,
	                                nl_recvmsg_msg_cb_t valid_handler, T *valid_handler_args)
	    : command_(command), flags_(flags), valid_handler_(valid_handler),
	      valid_handler_args_(valid_handler_args)
	{
	}

	template <typename T>
	NlWifiCommand<T>::~NlWifiCommand()
	{
		if (socket_) {
			nl_socket_free(socket_);
		}
	}

	template <typename T>
	int NlWifiCommand<T>::send(unsigned int interface_index)
	{
		// An interface index of 0 is invalid
		if (interface_index == 0) {
			return -1;
		}

		// Allocate a netlink socket
		if (!socket_) {
			socket_ = nl_socket_alloc();
			// Connect a generic netlink socket
			if (genl_connect(socket_)) {
				nl_socket_free(socket_);
				socket_ = nullptr;
				return -1;
			}
		}

		// Resolve Generic Netlink family name to numeric identifier
		int nl80211_id = genl_ctrl_resolve(socket_, "nl80211");
		if (nl80211_id < 0) {
			return -1;
		}

		// Allocate a new netlink message
		nl_msg *message = nlmsg_alloc();

		// Add Generic Netlink headers to the message
		genlmsg_put(message, NL_AUTO_PORT, NL_AUTO_SEQ, nl80211_id, 0, flags_, command_, 0);

		// Add an attribute containing the wireless interface index
		nla_put(message, NL80211_ATTR_IFINDEX, sizeof(interface_index), &interface_index);

		// Send the message
		if (nl_send_auto(socket_, message) < 0) {
			nlmsg_free(message);
			return -1;
		}

		// Allocate a callback handle
		nl_cb *callback = nl_cb_alloc(NL_CB_DEFAULT);
		int callback_arg = 1;

		// clang-format off
		// Set up an error callback
		nl_cb_err(callback, NL_CB_CUSTOM, [](sockaddr_nl *, nlmsgerr *nlerr, void *arg) -> int {
			int *callback_arg = static_cast<int *>(arg);
			*callback_arg = nlerr->error;
			return NL_STOP;
		}, &callback_arg);

		// Set up a callback for when ACKs are received
		nl_cb_set(callback, NL_CB_ACK, NL_CB_CUSTOM, [](nl_msg *, void *arg) -> int {
			int *callback_arg = static_cast<int *>(arg);
			*callback_arg = 0;
			return NL_STOP;
		}, &callback_arg);


		// Set up a callback for when the last message is received
		nl_cb_set(callback, NL_CB_FINISH, NL_CB_CUSTOM, [](nl_msg *, void *arg) -> int {
			int *callback_arg = static_cast<int *>(arg);
			*callback_arg = 0;
			return NL_SKIP;
		}, &callback_arg);
		// clang-format on

		// Set up a callback for when valid messages are received
		if (valid_handler_) {
			nl_cb_set(callback, NL_CB_VALID, NL_CB_CUSTOM, valid_handler_, valid_handler_args_);
		}

		// Keep receiving messages until callback_arg is set to 0 in one of the callbacks
		while (callback_arg > 0) {
			nl_recvmsgs(socket_, callback);
		}

		// Decrement callback's reference count
		nl_cb_put(callback);
		// Free the message
		nlmsg_free(message);

		return callback_arg;
	}
} // namespace KawaiiFi

#endif // NL_WIFI_COMMAND_H
