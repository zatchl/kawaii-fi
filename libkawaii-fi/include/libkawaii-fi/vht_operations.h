#ifndef VHT_OPERATIONS_H
#define VHT_OPERATIONS_H

#include "vht_capabilities.h"

#include <QMetaType>
#include <string_view>

class QDBusArgument;

enum class VhtChannelWidth { TwentyOrFortyMhz, EightyMhz, OneSixtyMhz, EightyPlusEightyMhz };

class VhtOperations {
public:
	[[nodiscard]] bool supported() const;
	[[nodiscard]] VhtChannelWidth channel_width() const;
	[[nodiscard]] unsigned int channel_center_segment_zero() const;
	[[nodiscard]] unsigned int channel_center_segment_one() const;
	[[nodiscard]] VhtMcs mcs_basic_one_ss() const;
	[[nodiscard]] VhtMcs mcs_basic_two_ss() const;
	[[nodiscard]] VhtMcs mcs_basic_three_ss() const;
	[[nodiscard]] VhtMcs mcs_basic_four_ss() const;
	[[nodiscard]] VhtMcs mcs_basic_five_ss() const;
	[[nodiscard]] VhtMcs mcs_basic_six_ss() const;
	[[nodiscard]] VhtMcs mcs_basic_seven_ss() const;
	[[nodiscard]] VhtMcs mcs_basic_eight_ss() const;

	void parse_ie(std::string_view ie_data);

	// Marshall the VHT Operation data into a D-Bus argument
	friend QDBusArgument &operator<<(QDBusArgument &argument, const VhtOperations &vht_op);

	// Retrieve the VHT Operation data from the D-Bus argument
	friend const QDBusArgument &operator>>(const QDBusArgument &argument, VhtOperations &vht_op);

private:
	bool supported_ = false;
	VhtChannelWidth channel_width_ = VhtChannelWidth::TwentyOrFortyMhz;
	unsigned int channel_center_segment_zero_ = 0;
	unsigned int channel_center_segment_one_ = 0;
	VhtMcs mcs_basic_one_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_basic_two_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_basic_three_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_basic_four_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_basic_five_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_basic_six_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_basic_seven_ss_ = VhtMcs::NotSupported;
	VhtMcs mcs_basic_eight_ss_ = VhtMcs::NotSupported;
};
Q_DECLARE_METATYPE(VhtOperations)

#endif // VHT_OPERATIONS_H
