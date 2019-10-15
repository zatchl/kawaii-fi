#include "libkawaii-fi/capabilities.h"

#include <cstdint>

namespace {
	const std::uint8_t ess_mask = 0x01;                      // 0000 0001
	const std::uint8_t ibss_mask = 0x02;                     // 0000 0010
	const std::uint8_t cf_pollable_mask = 0x04;              // 0000 0100
	const std::uint8_t cf_poll_request_mask = 0x08;          // 0000 1000
	const std::uint8_t privacy_mask = 0x10;                  // 0001 0000
	const std::uint8_t short_preamble_mask = 0x20;           // 0010 0000
	const std::uint8_t pbcc_mask = 0x40;                     // 0100 0000
	const std::uint8_t channel_agility_mask = 0x80;          // 1000 0000
	const std::uint8_t spectrum_management_mask = 0x01;      // 0000 0001
	const std::uint8_t short_slot_time_mask = 0x04;          // 0000 0100
	const std::uint8_t auto_power_save_delivery_mask = 0x08; // 0000 1000
	const std::uint8_t radio_measurement_mask = 0x10;        // 0001 0000
	const std::uint8_t dsss_ofdm_mask = 0x20;                // 0010 0000
	const std::uint8_t delayed_block_ack_mask = 0x40;        // 0100 0000
	const std::uint8_t immediate_block_ack_mask = 0x80;      // 1000 0000
} // namespace

namespace KawaiiFi {
	Capabilities::Capabilities(const char *bytes, int size) : bytes_(QByteArray(bytes, size)) {}

	bool Capabilities::ess() const
	{
		if (bytes().size() < 1) {
			return false;
		}
		return bytes()[0] & ess_mask;
	}

	bool Capabilities::ibss() const
	{
		if (bytes().size() < 1) {
			return false;
		}
		return bytes()[0] & ibss_mask;
	}

	bool Capabilities::cf_pollable() const
	{
		if (bytes().size() < 1) {
			return false;
		}
		return bytes()[0] & cf_pollable_mask;
	}

	bool Capabilities::cf_poll_request() const
	{
		if (bytes().size() < 1) {
			return false;
		}
		return bytes()[0] & cf_poll_request_mask;
	}

	bool Capabilities::privacy() const
	{
		if (bytes().size() < 1) {
			return false;
		}
		return bytes()[0] & privacy_mask;
	}

	bool Capabilities::short_preamble() const
	{
		if (bytes().size() < 1) {
			return false;
		}
		return bytes()[0] & short_preamble_mask;
	}

	bool Capabilities::pbcc() const
	{
		if (bytes().size() < 1) {
			return false;
		}
		return bytes()[0] & pbcc_mask;
	}

	bool Capabilities::channel_agility() const
	{
		if (bytes().size() < 1) {
			return false;
		}
		return bytes()[0] & channel_agility_mask;
	}

	bool Capabilities::spectrum_management() const
	{
		if (bytes().size() < 2) {
			return false;
		}
		return bytes()[1] & spectrum_management_mask;
	}

	bool Capabilities::short_slot_time() const
	{
		if (bytes().size() < 2) {
			return false;
		}
		return bytes()[1] & short_slot_time_mask;
	}

	bool Capabilities::auto_power_save_delivery() const
	{
		if (bytes().size() < 2) {
			return false;
		}
		return bytes()[1] & auto_power_save_delivery_mask;
	}

	bool Capabilities::radio_measurement() const
	{
		if (bytes().size() < 2) {
			return false;
		}
		return bytes()[1] & radio_measurement_mask;
	}

	bool Capabilities::dsss_ofdm() const
	{
		if (bytes().size() < 2) {
			return false;
		}
		return bytes()[1] & dsss_ofdm_mask;
	}

	bool Capabilities::delayed_block_ack() const
	{
		if (bytes().size() < 2) {
			return false;
		}
		return bytes()[1] & delayed_block_ack_mask;
	}

	bool Capabilities::immediate_block_ack() const
	{
		if (bytes().size() < 2) {
			return false;
		}
		return bytes()[1] & immediate_block_ack_mask;
	}

	const QByteArray &Capabilities::bytes() const { return bytes_; }
} // namespace KawaiiFi
