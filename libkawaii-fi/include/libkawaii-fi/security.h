#ifndef SECURITY_H
#define SECURITY_H

#include <QFlag>
#include <QString>
#include <QStringList>

namespace KawaiiFi::Security {
	enum class Protocol { None = 1 << 0, WEP = 1 << 1, WPA = 1 << 2, WPA2 = 1 << 3, WPA3 = 1 << 4 };

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
