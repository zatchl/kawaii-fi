#ifndef HT_OPERATIONS_H
#define HT_OPERATIONS_H

#include "ht_capabilities.h"
#include "information_element.h"

#include <QVector>
#include <cstdint>

enum class SecondaryChannelOffset { NoSecondaryChannel, Above, Below };

enum class HtProtection { None, Nonmember, TwentyMhz, NonHtMixed };

enum class PcoPhase { TwentyMhz, FortyMhz };

class HtOperations : public InformationElement {
public:
	HtOperations() = default;
	HtOperations(const InformationElement &ie);
	HtOperations(const char *bytes, int size);

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

	[[nodiscard]] QVector<std::uint8_t> rx_mcs() const;
	[[nodiscard]] unsigned int highest_supported_data_rate() const;
	[[nodiscard]] bool tx_mcs_defined() const;
	[[nodiscard]] bool tx_rx_mcs_equal() const;
	[[nodiscard]] unsigned int max_tx_spatial_streams() const;
	[[nodiscard]] bool tx_unequal_modulation() const;
};

inline const unsigned int WLAN_EID_HT_OPERATION = 61;

#endif // HT_OPERATIONS_H
