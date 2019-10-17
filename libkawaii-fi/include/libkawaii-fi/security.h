#ifndef SECURITY_H
#define SECURITY_H

#include <QFlag>
#include <QString>
#include <QStringList>

namespace KawaiiFi::Security {
	enum class Protocol {
		None = 1U << 0U,
		WEP = 1U << 1U,
		WPA = 1U << 2U,
		WPA2 = 1U << 3U,
		WPA3 = 1U << 4U
	};

	Q_DECLARE_FLAGS(Protocols, Security::Protocol)
	Q_DECLARE_OPERATORS_FOR_FLAGS(Protocols)

	QString security_protocol_to_string(Security::Protocol security_protocol);

	inline QString security_protocols_to_string(Protocols security_protocols,
	                                            const QString &delimeter = "");

	enum class CipherSuiteType { SameAsGroupCipher, WEP40, TKIP, CCMP, WEP104 };

	struct CipherSuite {
		const std::array<std::uint8_t, 3> oui = {0x00, 0x0f, 0xac};
		const CipherSuiteType type = CipherSuiteType::WEP40;
	};

	enum class AkmSuiteType { None, IEEE_8021X, PSK };

	struct AkmSuite {
		const std::array<std::uint8_t, 3> oui = {0x00, 0x0f, 0xac};
		const AkmSuiteType type = AkmSuiteType::IEEE_8021X;
	};
} // namespace KawaiiFi::Security

#endif // SECURITY_H
