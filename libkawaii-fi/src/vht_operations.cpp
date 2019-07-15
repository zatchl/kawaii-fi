#include "libkawaii-fi/vht_operations.h"

#include "libkawaii-fi/vht_capabilities.h"

QDBusArgument &operator<<(QDBusArgument &argument, const VhtOperations &vht_op)
{
	argument.beginStructure();
	argument << vht_op.supported << static_cast<int>(vht_op.channel_width)
	         << vht_op.channel_center_segment_zero << vht_op.channel_center_segment_one
	         << static_cast<int>(vht_op.mcs_basic_one_ss)
	         << static_cast<int>(vht_op.mcs_basic_two_ss)
	         << static_cast<int>(vht_op.mcs_basic_three_ss)
	         << static_cast<int>(vht_op.mcs_basic_four_ss)
	         << static_cast<int>(vht_op.mcs_basic_five_ss)
	         << static_cast<int>(vht_op.mcs_basic_six_ss)
	         << static_cast<int>(vht_op.mcs_basic_seven_ss)
	         << static_cast<int>(vht_op.mcs_basic_eight_ss);
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, VhtOperations &vht_op)
{
	int channel_width = 0;
	int mcs_basic_one_ss = 0;
	int mcs_basic_two_ss = 0;
	int mcs_basic_three_ss = 0;
	int mcs_basic_four_ss = 0;
	int mcs_basic_five_ss = 0;
	int mcs_basic_six_ss = 0;
	int mcs_basic_seven_ss = 0;
	int mcs_basic_eight_ss = 0;
	argument.beginStructure();
	argument >> vht_op.supported >> channel_width >> vht_op.channel_center_segment_zero >>
	        vht_op.channel_center_segment_one >> mcs_basic_one_ss >> mcs_basic_two_ss >>
	        mcs_basic_three_ss >> mcs_basic_four_ss >> mcs_basic_five_ss >> mcs_basic_six_ss >>
	        mcs_basic_seven_ss >> mcs_basic_eight_ss;
	argument.endStructure();
	vht_op.channel_width = static_cast<VhtChannelWidth>(channel_width);
	vht_op.mcs_basic_one_ss = static_cast<VhtMcs>(mcs_basic_one_ss);
	vht_op.mcs_basic_two_ss = static_cast<VhtMcs>(mcs_basic_two_ss);
	vht_op.mcs_basic_three_ss = static_cast<VhtMcs>(mcs_basic_three_ss);
	vht_op.mcs_basic_four_ss = static_cast<VhtMcs>(mcs_basic_four_ss);
	vht_op.mcs_basic_five_ss = static_cast<VhtMcs>(mcs_basic_five_ss);
	vht_op.mcs_basic_six_ss = static_cast<VhtMcs>(mcs_basic_six_ss);
	vht_op.mcs_basic_seven_ss = static_cast<VhtMcs>(mcs_basic_seven_ss);
	vht_op.mcs_basic_eight_ss = static_cast<VhtMcs>(mcs_basic_eight_ss);
	return argument;
}
