#ifndef HT_OPERATIONS_H
#define HT_OPERATIONS_H

#include "ht_capabilities.h"

#include <QDBusArgument>
#include <QMetaType>
#include <QVector>
#include <cstdint>
#include <string_view>

enum class SecondaryChannelOffset { NoSecondaryChannel, Above, Below };

enum class HtProtection { None, Nonmember, TwentyMhz, NonHtMixed };

enum class PcoPhase { TwentyMhz, FourtyMhz };

class HtOperations {
public:
	[[nodiscard]] bool supported() const;
	[[nodiscard]] unsigned int primary_channel() const;
	[[nodiscard]] SecondaryChannelOffset secondary_channel_offset() const;
	[[nodiscard]] HtSupportedChannelWidth supported_channel_width() const;
	[[nodiscard]] bool rifs() const;
	[[nodiscard]] HtProtection ht_protection() const;
	[[nodiscard]] bool non_greenfield_stas_present() const;
	[[nodiscard]] bool obss_non_ht_stas_present() const;
	[[nodiscard]] unsigned int center_freq_segment_two() const;
	[[nodiscard]] bool dual_beacon() const;
	[[nodiscard]] bool dual_cts_protection() const;
	[[nodiscard]] bool stbc_beacon() const;
	[[nodiscard]] bool lsig_txop_protection_full_support() const;
	[[nodiscard]] bool pco_active() const;
	[[nodiscard]] PcoPhase pco_phase() const;

	[[nodiscard]] const QVector<std::uint8_t> &rx_mcs() const;
	[[nodiscard]] QVector<std::uint8_t> &rx_mcs();
	[[nodiscard]] unsigned int highest_supported_data_rate() const;
	[[nodiscard]] bool tx_mcs_defined() const;
	[[nodiscard]] bool tx_rx_mcs_equal() const;
	[[nodiscard]] unsigned int max_tx_spatial_streams() const;
	[[nodiscard]] bool tx_unequal_modulation() const;

	void parse_ie(std::string_view ie_data);
	void set_supported(bool supported);
	void set_primary_channel(unsigned int primary_channel);
	void set_secondary_channel_offset(SecondaryChannelOffset secondary_channel_offset);
	void set_supported_channel_width(HtSupportedChannelWidth supported_channel_width);
	void set_rifs(bool rifs);
	void set_ht_protection(HtProtection ht_protection);
	void set_non_greenfield_stas_present(bool non_greenfield_stas_present);
	void set_obss_non_ht_stas_present(bool obss_non_ht_stas_present);
	void set_center_freq_segment_two(unsigned int center_freq_segment_two);
	void set_dual_beacon(bool dual_beacon);
	void set_dual_cts_protection(bool dual_cts_protection);
	void set_stbc_beacon(bool stbc_beacon);
	void set_lsig_txop_protection_full_support(bool lsig_txop_protection_full_support);
	void set_pco_active(bool pco_active);
	void set_pco_phase(PcoPhase pco_phase);

	void set_rx_mcs(const QVector<std::uint8_t> &rx_mcs);
	void set_highest_supported_data_rate(unsigned int highest_supported_data_rate);
	void set_tx_mcs_defined(bool tx_mcs_defined);
	void set_tx_rx_mcs_equal(bool tx_rx_mcs_equal);
	void set_max_tx_spatial_streams(unsigned int max_tx_spatial_streams);
	void set_tx_unequal_modulation(bool tx_unequal_modulation);

private:
	bool supported_ = false;
	unsigned int primary_channel_ = 0;
	SecondaryChannelOffset secondary_channel_offset_ = SecondaryChannelOffset::NoSecondaryChannel;
	HtSupportedChannelWidth supported_channel_width_ = HtSupportedChannelWidth::TwentyMhz;
	bool rifs_ = false;
	HtProtection ht_protection_ = HtProtection::None;
	bool non_greenfield_stas_present_ = false;
	bool obss_non_ht_stas_present_ = false;
	unsigned int center_freq_segment_two_ = 0;
	bool dual_beacon_ = false;
	bool dual_cts_protection_ = false;
	bool stbc_beacon_ = false;
	bool lsig_txop_protection_full_support_ = false;
	bool pco_active_ = false;
	PcoPhase pco_phase_ = PcoPhase::TwentyMhz;

	QVector<std::uint8_t> rx_mcs_;
	unsigned int highest_supported_data_rate_ = 0;
	bool tx_mcs_defined_ = false;
	bool tx_rx_mcs_equal_ = true;
	unsigned int max_tx_spatial_streams_ = 0;
	bool tx_unequal_modulation_ = false;
};
Q_DECLARE_METATYPE(HtOperations)

// Marshall the HT Operation data into a D-Bus argument
QDBusArgument &operator<<(QDBusArgument &argument, const HtOperations &ht_op);

// Retrieve the HT Operation data from the D-Bus argument
const QDBusArgument &operator>>(const QDBusArgument &argument, HtOperations &ht_op);

#endif // HT_OPERATIONS_H
