#include "libkawaii-fi/standard.h"

#include <QString>
#include <QStringList>

namespace KawaiiFi {
	QString standard_to_string(Standard standard)
	{
		switch (standard) {
		case Standard::B:
			return "b";
		case Standard::G:
			return "g";
		case Standard::N:
			return "n";
		case Standard::A:
			return "a";
		case Standard::AC:
			return "ac";
		case Standard::AX:
			return "ax";
		}

		return "";
	}

	QString standards_to_string(Standards standards, const QString &delimeter)
	{
		QStringList standard_strings;
		const auto all_standards = {Standard::B, Standard::G,  Standard::N,
		                            Standard::A, Standard::AC, Standard::AX};
		for (Standard standard : all_standards) {
			if (standards.testFlag(standard)) {
				standard_strings.append(standard_to_string(standard));
			}
		}

		return standard_strings.join(delimeter);
	}
} // namespace KawaiiFi
