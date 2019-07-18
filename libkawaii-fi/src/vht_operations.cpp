#include "libkawaii-fi/vht_operations.h"

#include "libkawaii-fi/vht_capabilities.h"

#include <QDBusArgument>

namespace {
	const unsigned int vht_operation_ie_length = 5;
}

bool VhtOperations::supported() const { return supported_; }

VhtChannelWidth VhtOperations::channel_width() const { return channel_width_; }

unsigned int VhtOperations::channel_center_segment_zero() const
{
	return channel_center_segment_zero_;
}

unsigned int VhtOperations::channel_center_segment_one() const
{
	return channel_center_segment_one_;
}

VhtMcs VhtOperations::mcs_basic_one_ss() const { return mcs_basic_one_ss_; }

VhtMcs VhtOperations::mcs_basic_two_ss() const { return mcs_basic_two_ss_; }

VhtMcs VhtOperations::mcs_basic_three_ss() const { return mcs_basic_three_ss_; }

VhtMcs VhtOperations::mcs_basic_four_ss() const { return mcs_basic_four_ss_; }

VhtMcs VhtOperations::mcs_basic_five_ss() const { return mcs_basic_five_ss_; }

VhtMcs VhtOperations::mcs_basic_six_ss() const { return mcs_basic_six_ss_; }

VhtMcs VhtOperations::mcs_basic_seven_ss() const { return mcs_basic_seven_ss_; }

VhtMcs VhtOperations::mcs_basic_eight_ss() const { return mcs_basic_eight_ss_; }

void VhtOperations::parse_ie(std::string_view ie_data)
{
	if (ie_data.size() != vht_operation_ie_length) {
		return;
	}

	supported_ = true;
	switch (ie_data[0]) {
	case 0:
		channel_width_ = VhtChannelWidth::TwentyOrFortyMhz;
		break;
	case 1:
		channel_width_ = VhtChannelWidth::EightyMhz;
		break;
	case 2:
		channel_width_ = VhtChannelWidth::OneSixtyMhz;
		break;
	case 3:
		channel_width_ = VhtChannelWidth::EightyPlusEightyMhz;
		break;
	}
	channel_center_segment_zero_ = static_cast<unsigned char>(ie_data[1]);
	channel_center_segment_one_ = static_cast<unsigned char>(ie_data[2]);
}

QDBusArgument &operator<<(QDBusArgument &argument, const VhtOperations &vht_op)
{
	argument.beginStructure();
	argument << vht_op.supported_ << static_cast<int>(vht_op.channel_width_)
	         << vht_op.channel_center_segment_zero_ << vht_op.channel_center_segment_one_
	         << static_cast<int>(vht_op.mcs_basic_one_ss_)
	         << static_cast<int>(vht_op.mcs_basic_two_ss_)
	         << static_cast<int>(vht_op.mcs_basic_three_ss_)
	         << static_cast<int>(vht_op.mcs_basic_four_ss_)
	         << static_cast<int>(vht_op.mcs_basic_five_ss_)
	         << static_cast<int>(vht_op.mcs_basic_six_ss_)
	         << static_cast<int>(vht_op.mcs_basic_seven_ss_)
	         << static_cast<int>(vht_op.mcs_basic_eight_ss_);
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, VhtOperations &vht_op)
{
	argument.beginStructure();
	vht_op.supported_ = qdbus_cast<bool>(argument);
	vht_op.channel_width_ = static_cast<VhtChannelWidth>(qdbus_cast<int>(argument));
	vht_op.channel_center_segment_zero_ = qdbus_cast<unsigned int>(argument);
	vht_op.channel_center_segment_one_ = qdbus_cast<unsigned int>(argument);
	vht_op.mcs_basic_one_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_op.mcs_basic_two_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_op.mcs_basic_three_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_op.mcs_basic_four_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_op.mcs_basic_five_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_op.mcs_basic_six_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_op.mcs_basic_seven_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));
	vht_op.mcs_basic_eight_ss_ = static_cast<VhtMcs>(qdbus_cast<int>(argument));

	argument.endStructure();
	return argument;
}
