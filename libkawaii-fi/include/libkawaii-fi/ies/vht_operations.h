#ifndef VHT_OPERATIONS_H
#define VHT_OPERATIONS_H

#include "information_element.h"
#include "vht_capabilities.h"

#include <string_view>

class QStandardItem;

enum class VhtChannelWidth { TwentyOrFortyMhz, EightyMhz, OneSixtyMhz, EightyPlusEightyMhz };

class VhtOperations : public InformationElement {
public:
	VhtOperations() = default;
	explicit VhtOperations(const std::string_view &bytes);

	[[nodiscard]] QStandardItem *standard_item() const override;

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
};

inline const unsigned int WLAN_EID_VHT_OPERATION = 192;

#endif // VHT_OPERATIONS_H
