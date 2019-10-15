#include "libkawaii-fi/security.h"

#include <QString>
#include <QStringList>

namespace KawaiiFi::Security {
	QString security_protocol_to_string(Security::Protocol security_protocol)
	{
		switch (security_protocol) {
		case Security::Protocol::None:
			return "None";
		case Security::Protocol::WEP:
			return "WEP";
		case Security::Protocol::WPA:
			return "WPA";
		case Security::Protocol::WPA2:
			return "WPA2";
		case Security::Protocol::WPA3:
			return "WPA3";
		}

		return "";
	}

	QString security_protocols_to_string(Security::Protocols security_protocols,
	                                     const QString &delimeter)
	{
		QStringList security_protocol_list;
		const auto all_security_protocols = {Security::Protocol::None, Security::Protocol::WEP,
		                                     Security::Protocol::WPA, Security::Protocol::WPA2,
		                                     Security::Protocol::WPA3};
		for (Security::Protocol security_protocol : all_security_protocols) {
			if (security_protocols.testFlag(security_protocol)) {
				security_protocol_list.append(security_protocol_to_string(security_protocol));
			}
		}

		return security_protocol_list.join(delimeter);
	}
} // namespace KawaiiFi::Security
