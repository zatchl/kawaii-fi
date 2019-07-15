#ifndef HT_OPERATIONS_H
#define HT_OPERATIONS_H

#include "ht_capabilities.h"

#include <QDBusArgument>
#include <QMetaType>
#include <QVector>
#include <cstdint>

enum class SecondaryChannelOffset { NoSecondaryChannel, Above, Below };

enum class HtProtection { None, Nonmember, TwentyMhz, NonHtMixed };

enum class PcoPhase { TwentyMhz, FourtyMhz };

struct HtOperations {
	bool supported = false;
	unsigned int primary_channel = 0;
	SecondaryChannelOffset secondary_channel_offset = SecondaryChannelOffset::NoSecondaryChannel;
	HtSupportedChannelWidth supported_channel_width = HtSupportedChannelWidth::TwentyMhz;
	bool rifs = false;
	HtProtection ht_protection = HtProtection::None;
	bool non_greenfield_stas_present = false;
	bool obss_non_ht_stas_present = false;
	unsigned int center_freq_segment_two = 0;
	bool dual_beacon = false;
	bool dual_cts_protection = false;
	bool stbc_beacon = false;
	bool lsig_txop_protection_full_support = false;
	bool pco_active = false;
	PcoPhase pco_phase = PcoPhase::TwentyMhz;

	QVector<std::uint8_t> rx_mcs;
	unsigned int highest_supported_data_rate = 0;
	bool tx_mcs_defined = false;
	bool tx_rx_mcs_equal = true;
	unsigned int max_tx_spatial_streams = 0;
	bool tx_unequal_modulation = false;
};
Q_DECLARE_METATYPE(HtOperations)

// Marshall the HT Operation data into a D-Bus argument
QDBusArgument &operator<<(QDBusArgument &argument, const HtOperations &ht_op);

// Retrieve the HT Operation data from the D-Bus argument
const QDBusArgument &operator>>(const QDBusArgument &argument, HtOperations &ht_op);

#endif // HT_OPERATIONS_H
