#include "libkawaii-fi/access_point.h"

#include "libkawaii-fi/capabilities.h"
#include "libkawaii-fi/channel.h"
#include "libkawaii-fi/ies/ht_capabilities.h"
#include "libkawaii-fi/ies/ht_operations.h"
#include "libkawaii-fi/ies/ie_variant.h"
#include "libkawaii-fi/ies/robust_security_network.h"
#include "libkawaii-fi/ies/ssid.h"
#include "libkawaii-fi/ies/supported_rates.h"
#include "libkawaii-fi/ies/vendor_specific.h"
#include "libkawaii-fi/ies/vht_capabilities.h"
#include "libkawaii-fi/ies/vht_operations.h"
#include "libkawaii-fi/ies/wpa.h"
#include "libkawaii-fi/security.h"

#include <QList>
#include <QSet>
#include <algorithm>
#include <array>
#include <variant>

namespace {
	const double ht_vht_short_gi_us = 0.4;
	const double ht_vht_long_gi_us = 0.8;

	const double ofdm_symbol_duration_us = 3.2;

	int ht_vht_data_subcarriers(ChannelWidth channel_width)
	{
		switch (channel_width) {
		case ChannelWidth::TwentyMhz:
			return 52;
		case ChannelWidth::FortyMhz:
			return 108;
		case ChannelWidth::EightyMhz:
			return 234;
		case ChannelWidth::OneSixtyMhz:
		case ChannelWidth::EightyPlusEightyMhz:
			return 468;
		default:
			return 0;
		}
	}

	bool ht_short_gi(const HtCapabilities &ht_cap, ChannelWidth channel_width)
	{
		switch (channel_width) {
		case ChannelWidth::TwentyMhz:
			return ht_cap.short_gi_20_mhz();
		case ChannelWidth::FortyMhz:
			return ht_cap.short_gi_40_mhz();
		default:
			return false;
		}
	}

	double ht_max_rate(const HtCapabilities &ht_cap, ChannelWidth channel_width)
	{
		int max_ss = 0;
		HtMcs mcs = {HtModulation::None, 0};
		const std::array<HtMcs, 4> ht_mcs = ht_cap.rx_mcs();
		for (unsigned int i = 0; i < ht_mcs.size(); ++i) {
			if (ht_mcs[i].modulation == HtModulation::None) {
				continue;
			}
			max_ss = static_cast<int>(i + 1);
			mcs = ht_mcs[i];
		}
		return (ht_vht_data_subcarriers(channel_width) * static_cast<int>(mcs.modulation) *
		        mcs.coding * max_ss) /
		       (ofdm_symbol_duration_us +
		        (ht_short_gi(ht_cap, channel_width) ? ht_vht_short_gi_us : ht_vht_long_gi_us));
	}

	int vht_bpscs(VhtMcs mcs)
	{
		switch (mcs) {
		case VhtMcs::OneThroughSeven:
			return 6;
		case VhtMcs::OneThroughEight:
		case VhtMcs::OneThroughNine:
			return 8;
		case VhtMcs::NotSupported:
			return 0;
		}
		return 0;
	}

	double vht_coding(VhtMcs mcs)
	{
		switch (mcs) {
		case VhtMcs::OneThroughSeven:
			return 5.0 / 6;
		case VhtMcs::OneThroughEight:
			return 3.0 / 4;
		case VhtMcs::OneThroughNine:
			return 5.0 / 6;
		case VhtMcs::NotSupported:
			return 0;
		}
		return 0;
	}

	bool vht_short_gi(const VhtCapabilities &vht_cap, const HtCapabilities &ht_cap,
	                  ChannelWidth channel_width)
	{
		switch (channel_width) {
		case ChannelWidth::TwentyMhz:
			return ht_cap.short_gi_20_mhz();
		case ChannelWidth::FortyMhz:
			return ht_cap.short_gi_40_mhz();
		case ChannelWidth::EightyMhz:
			return vht_cap.short_gi_80_mhz();
		case ChannelWidth::OneSixtyMhz:
		case ChannelWidth::EightyPlusEightyMhz:
			return vht_cap.short_gi_160_mhz();
		default:
			return false;
		}
	}

	double vht_max_rate(const VhtCapabilities &vht_cap, const HtCapabilities &ht_cap,
	                    ChannelWidth channel_width)
	{
		int max_ss = 0;
		VhtMcs mcs = VhtMcs::NotSupported;
		const std::array<VhtMcs, 8> vht_mcs = vht_cap.mcs_rx();
		for (unsigned int i = 0; i < vht_mcs.size(); ++i) {
			if (vht_mcs[i] == VhtMcs::NotSupported) {
				break;
			}
			max_ss = static_cast<int>(i + 1);
			mcs = vht_mcs[i];
		}
		return (ht_vht_data_subcarriers(channel_width) * vht_bpscs(mcs) * vht_coding(mcs) *
		        max_ss) /
		       (ofdm_symbol_duration_us + (vht_short_gi(vht_cap, ht_cap, channel_width)
		                                           ? ht_vht_short_gi_us
		                                           : ht_vht_long_gi_us));
	}

	const QVector<QColor> colors = {
	        QColor(191, 97, 106),  QColor(208, 135, 112), QColor(163, 190, 140),
	        QColor(180, 142, 173), QColor(94, 129, 172),  QColor(235, 203, 139),
	        QColor(76, 86, 106),   QColor(143, 188, 187), QColor(222, 53, 106),
	        QColor(33, 101, 131),  QColor(255, 185, 97),  QColor(200, 218, 211),
	        QColor(75, 63, 114),   QColor(105, 113, 117), QColor(168, 218, 220),
	        QColor(229, 89, 52),   QColor(242, 181, 212), QColor(50, 147, 111),
	        QColor(191, 239, 69),  QColor(66, 212, 244),  QColor(228, 182, 96),
	        QColor(29, 106, 150),  QColor(155, 207, 184), QColor(188, 95, 106),
	        QColor(80, 78, 99),    QColor(154, 27, 39),   QColor(107, 121, 158),
	        QColor(10, 91, 84),    QColor(217, 207, 231), QColor(255, 162, 137),
	        QColor(112, 111, 171), QColor(157, 30, 49),   QColor(122, 45, 89),
	        QColor(55, 65, 154),   QColor(235, 151, 114), QColor(105, 93, 133),
	        QColor(166, 194, 206)};

	QColor random_color()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(0, colors.size() - 1);
		return colors[distr(gen)];
	}
} // namespace

const QString &AccessPoint::bssid() const { return bssid_; }

QString AccessPoint::ssid() const
{
	return information_elements_.value(WLAN_EID_SSID, InformationElement()).bytes();
}

ConnectionStatus AccessPoint::connection_status() const { return connection_status_; }
const QColor &AccessPoint::color() const { return color_; }

int AccessPoint::signal_strength_mbm() const { return signal_strength_mbm_; }

double AccessPoint::signal_strength_dbm() const
{
	const int mbm_per_dbm = 100;
	return static_cast<double>(signal_strength_mbm_) / mbm_per_dbm;
}

unsigned int AccessPoint::frequency() const { return frequency_; }

unsigned int AccessPoint::age_ms() const { return age_ms_; }

const QVector<Protocol> &AccessPoint::protocols() const { return protocols_; }

QVector<Protocol> &AccessPoint::protocols() { return protocols_; }

QStringList AccessPoint::supported_rates() const
{
	QSet<double> rates;
	QSet<double> basic_rates;

	for (const auto &ie : ies_) {
		if (auto supp_rates = std::get_if<SupportedRates>(&ie)) {
			rates.unite(supp_rates->rates());
			basic_rates.unite(supp_rates->basic_rates());
		}
	}

	// We want the result to be sorted
	// QSets can't be sorted so we create a separate list and sort the list
	QList rate_list = rates.toList();
	std::sort(rate_list.begin(), rate_list.end());

	// Add an asterisk after all the basic rates
	QStringList rate_string_list;
	for (const double rate : rate_list) {
		rate_string_list.append(basic_rates.contains(rate) ? QString("%0*").arg(rate)
		                                                   : QString::number(rate));
	}
	return rate_string_list;
}

double AccessPoint::max_rate() const
{
	const HtCapabilities *ht_cap = nullptr;
	const VhtCapabilities *vht_cap = nullptr;

	for (const auto &ie : ies_) {
		if (std::holds_alternative<HtCapabilities>(ie)) {
			ht_cap = &std::get<HtCapabilities>(ie);
			continue;
		}

		if (std::holds_alternative<VhtCapabilities>(ie)) {
			vht_cap = &std::get<VhtCapabilities>(ie);
			continue;
		}
	}

	if (vht_cap && ht_cap) {
		return vht_max_rate(*vht_cap, *ht_cap, channel_width());
	}

	if (ht_cap) {
		return ht_max_rate(*ht_cap, channel_width());
	}

	QSet<double> rates;
	for (const auto &ie : ies_) {
		if (auto supp_rates = std::get_if<SupportedRates>(&ie)) {
			rates.unite(supp_rates->rates());
		}
	}

	return *std::max_element(rates.begin(), rates.end());
}

const Capabilities &AccessPoint::capabilities() const { return capabilities_; }

Capabilities &AccessPoint::capabilites() { return capabilities_; }
const QVector<IeVariant> &AccessPoint::information_elements() const { return ies_; }




ChannelWidth AccessPoint::channel_width() const
{
	if (information_elements_.contains(WLAN_EID_VHT_OPERATION)) {
		const VhtOperations &vht_operations = information_elements_.value(WLAN_EID_VHT_OPERATION);
		switch (vht_operations.channel_width()) {
		case VhtChannelWidth::TwentyOrFortyMhz:
			break;
		case VhtChannelWidth::EightyMhz:
			return ChannelWidth::EightyMhz;
		case VhtChannelWidth::OneSixtyMhz:
			return ChannelWidth::OneSixtyMhz;
		case VhtChannelWidth::EightyPlusEightyMhz:
			return ChannelWidth::EightyPlusEightyMhz;
		}
	}
	if (information_elements_.contains(WLAN_EID_HT_OPERATION)) {
		const HtOperations &ht_operations = information_elements_.value(WLAN_EID_HT_OPERATION);
		if (ht_operations.secondary_channel_offset() !=
		    SecondaryChannelOffset::NoSecondaryChannel) {
			return ChannelWidth::FortyMhz;
		}
	}
	return ChannelWidth::TwentyMhz;
}

namespace {
	QString calculate_ssid(const QVector<IeVariant> &ies)
	{
		for (const auto &ie : ies) {
			if (auto ssid_ie = std::get_if<Ssid>(&ie)) {
				return ssid_ie->bytes();
			}
		}
		return QString();
	}

	QVector<SecurityProtocol> calculate_security(const Capabilities &capabilities,
	                                             const QVector<IeVariant> &ies)
	{
		if (!capabilities.privacy()) {
			return {SecurityProtocol::None};
		}

		QVector<SecurityProtocol> security;

		for (const auto &ie : ies) {
			if (std::holds_alternative<Wpa>(ie)) {
				security.append(SecurityProtocol::WPA);
			}
			if (std::holds_alternative<RobustSecurityNetwork>(ie)) {
				security.append(SecurityProtocol::WPA2);
			}
		}
QVector<SecurityProtocol> AccessPoint::security() const
{
	if (!capabilities_.privacy()) {
		return {SecurityProtocol::None};
	}

	const bool contains_wpa_ie = contains_vendor_element(WPA_OUI, WPA_VENDOR_TYPE);

	if (!information_elements_.contains(WLAN_EID_RSN) && !contains_wpa_ie) {
		return {SecurityProtocol::WEP};
	}

	AkmSuiteType calculate_authentication(const QVector<IeVariant> &ies)
	{
		for (const auto &ie : ies) {
			if (auto rsn = std::get_if<RobustSecurityNetwork>(&ie)) {
				return !rsn->akm_suites().empty() ? rsn->akm_suites()[0].type : AkmSuiteType::None;
			}
		}

		for (const auto &ie : ies) {
			if (auto wpa = std::get_if<Wpa>(&ie)) {
				return !wpa->akm_suites().empty() ? wpa->akm_suites()[0].type : AkmSuiteType::None;
			}
		}

		return AkmSuiteType::None;
	}
} // namespace

	return security;
}

AkmSuiteType AccessPoint::authentication() const
{
	// Check the RSN IE
	if (information_elements_.contains(WLAN_EID_RSN)) {
		const auto akm_suites =
		        RobustSecurityNetwork(information_elements_.value(WLAN_EID_RSN)).akm_suites();
		if (akm_suites.size() > 0) {
			return akm_suites[0].type;
		}
	}

	// Check the WPA IE
	auto it = information_elements_.find(WLAN_EID_VENDOR_SPECIFIC);
	while (it != information_elements_.end() && it.key() == WLAN_EID_VENDOR_SPECIFIC) {
		const VendorSpecific v_ie = VendorSpecific(it.value());
		if (v_ie.oui() == WPA_OUI && v_ie.type() == WPA_VENDOR_TYPE) {
			const Wpa wpa_ie = Wpa(v_ie);
			const auto akm_suites = Wpa(v_ie).akm_suites();
			if (akm_suites.size() > 0) {
				return akm_suites[0].type;
			}
			break;
		}
		++it;
	}

	return AkmSuiteType::None;
}

void AccessPoint::set_bssid(const QString &bssid) { bssid_ = bssid; }

void AccessPoint::set_connection_status(ConnectionStatus connection_status)
{
	connection_status_ = connection_status;
}

void AccessPoint::set_signal_strength_mbm(int signal_strength_mbm)
{
	signal_strength_mbm_ = signal_strength_mbm;
}

void AccessPoint::set_frequency(unsigned int frequency) { frequency_ = frequency; }

void AccessPoint::set_age_ms(unsigned int age_ms) { age_ms_ = age_ms; }

void AccessPoint::set_capabilities(const char *bytes, int size)
{
	capabilities_ = Capabilities(bytes, size);
}

void AccessPoint::set_protocols(const QVector<Protocol> &protocols) { protocols_ = protocols; }

QDBusArgument &operator<<(QDBusArgument &argument, const AccessPoint &ap)
{
	QVector<int> protocols;
	for (Protocol p : ap.protocols()) {
		protocols.append(static_cast<int>(p));
	}
	argument.beginStructure();
	argument << ap.bssid() << static_cast<int>(ap.connection_status()) << ap.signal_strength_mbm()
	         << ap.frequency() << ap.age_ms() << protocols << ap.capabilities()
	         << ap.information_elements();
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, AccessPoint &ap)
{
	argument.beginStructure();
	ap.set_bssid(qdbus_cast<QString>(argument));
	ap.set_connection_status(static_cast<ConnectionStatus>(qdbus_cast<int>(argument)));
	ap.set_signal_strength_mbm(qdbus_cast<int>(argument));
	ap.set_frequency(qdbus_cast<unsigned int>(argument));
	ap.set_age_ms(qdbus_cast<unsigned int>(argument));
	for (int i : qdbus_cast<QVector<int>>(argument)) {
		ap.protocols().append(static_cast<Protocol>(i));
	}
	argument >> ap.capabilites();
	argument >> ap.information_elements();
	argument.endStructure();
	return argument;
}

bool operator==(const AccessPoint &lhs, const AccessPoint &rhs)
{
	return lhs.bssid() == rhs.bssid();
}

bool operator!=(const AccessPoint &lhs, const AccessPoint &rhs) { return !(lhs == rhs); }
