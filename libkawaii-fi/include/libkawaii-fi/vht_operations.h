#ifndef VHT_OPERATIONS_H
#define VHT_OPERATIONS_H

#include "vht_capabilities.h"

#include <QDBusArgument>
#include <QMetaType>

enum class VhtChannelWidth { TwentyOrFortyMhz, EightyMhz, OneSixtyMhz, EightyPlusEightyMhz };

struct VhtOperations {
	bool supported = false;
	VhtChannelWidth channel_width = VhtChannelWidth::TwentyOrFortyMhz;
	unsigned int channel_center_segment_zero = 0;
	unsigned int channel_center_segment_one = 0;
	VhtMcs mcs_basic_one_ss = VhtMcs::NotSupported;
	VhtMcs mcs_basic_two_ss = VhtMcs::NotSupported;
	VhtMcs mcs_basic_three_ss = VhtMcs::NotSupported;
	VhtMcs mcs_basic_four_ss = VhtMcs::NotSupported;
	VhtMcs mcs_basic_five_ss = VhtMcs::NotSupported;
	VhtMcs mcs_basic_six_ss = VhtMcs::NotSupported;
	VhtMcs mcs_basic_seven_ss = VhtMcs::NotSupported;
	VhtMcs mcs_basic_eight_ss = VhtMcs::NotSupported;
};
Q_DECLARE_METATYPE(VhtOperations)

// Marshall the VHT Operation data into a D-Bus argument
QDBusArgument &operator<<(QDBusArgument &argument, const VhtOperations &vht_op);

// Retrieve the VHT Operation data from the D-Bus argument
const QDBusArgument &operator>>(const QDBusArgument &argument, VhtOperations &vht_op);

#endif // VHT_OPERATIONS_H
