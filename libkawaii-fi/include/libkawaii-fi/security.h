#ifndef SECURITY_H
#define SECURITY_H

#include <QHash>
#include <array>

enum class SecurityProtocol { None, WEP, WPA, WPA2, WPA3 };

inline uint qHash(SecurityProtocol key, uint seed) { return qHash(static_cast<int>(key), seed); }

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

#endif // SECURITY_H
