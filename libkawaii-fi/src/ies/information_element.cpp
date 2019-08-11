#include "libkawaii-fi/ies/information_element.h"

#include <QDBusArgument>

InformationElement::InformationElement(const QByteArray &bytes) : bytes_(bytes) {}

InformationElement::InformationElement(const char *bytes, int size)
    : bytes_(QByteArray(bytes, size))
{
}

const QByteArray &InformationElement::bytes() const { return bytes_; }

QByteArray &InformationElement::bytes() { return bytes_; }

QDBusArgument &operator<<(QDBusArgument &argument, const InformationElement &ie)
{
	argument.beginStructure();
	argument << ie.bytes_;
	argument.endStructure();
	return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, InformationElement &ie)
{
	argument.beginStructure();
	argument >> ie.bytes_;
	argument.endStructure();
	return argument;
}
