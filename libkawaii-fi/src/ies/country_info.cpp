#include "libkawaii-fi/ies/country_info.h"

#include "libkawaii-fi/ies/information_element.h"

#include <QByteArray>
#include <cstdint>

CountryInfo::CountryInfo(const InformationElement &ie) : InformationElement(ie.bytes()) {}

QString CountryInfo::country_code() const
{
	if (bytes().size() < 2) {
		return "";
	}
	return QString("%0%1").arg(bytes()[0]).arg(bytes()[1]);
}

Environment CountryInfo::environment() const
{
	if (bytes().size() < 3) {
		return Environment::Any;
	}
	switch (bytes()[2]) {
	case ' ':
		return Environment::Any;
	case 'I':
	case 'i':
		return Environment::Indoor;
	case 'O':
	case 'o':
		return Environment::Outdoor;
	default:
		return Environment::Any;
	}
}

QVector<ChannelPowerConstraint> CountryInfo::channel_constraints() const
{
	QVector<ChannelPowerConstraint> channel_constraints;
	auto it = bytes().begin() + 3;
	while (it + 3 < bytes().end()) {
		channel_constraints.append({static_cast<std::uint8_t>(*it),
		                            static_cast<std::uint8_t>(*(it + 1)),
		                            static_cast<std::uint8_t>(*(it + 2))});
		it += 3;
	}
	return channel_constraints;
}
