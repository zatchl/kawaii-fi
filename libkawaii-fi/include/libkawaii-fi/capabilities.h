#ifndef CAPABILITIES_H
#define CAPABILITIES_H

#include <QByteArray>

namespace KawaiiFi {
	class Capabilities {
	public:
		Capabilities() = default;
		Capabilities(const char *bytes, int size);

		[[nodiscard]] bool ess() const;
		[[nodiscard]] bool ibss() const;
		[[nodiscard]] bool cf_pollable() const;
		[[nodiscard]] bool cf_poll_request() const;
		[[nodiscard]] bool privacy() const;
		[[nodiscard]] bool short_preamble() const;
		[[nodiscard]] bool pbcc() const;
		[[nodiscard]] bool channel_agility() const;
		[[nodiscard]] bool spectrum_management() const;
		[[nodiscard]] bool short_slot_time() const;
		[[nodiscard]] bool auto_power_save_delivery() const;
		[[nodiscard]] bool radio_measurement() const;
		[[nodiscard]] bool dsss_ofdm() const;
		[[nodiscard]] bool delayed_block_ack() const;
		[[nodiscard]] bool immediate_block_ack() const;

		[[nodiscard]] const QByteArray &bytes() const;

	private:
		QByteArray bytes_;
	};
} // namespace KawaiiFi

#endif // CAPABILITIES_H
