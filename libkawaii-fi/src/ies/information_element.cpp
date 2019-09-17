#include "libkawaii-fi/ies/information_element.h"

#include <QStandardItem>
#include <cstdint>

InformationElement::InformationElement(const QByteArray &bytes) : bytes_(bytes) {}

InformationElement::InformationElement(const char *bytes, int size)
    : bytes_(QByteArray(bytes, size))
{
}

const QByteArray &InformationElement::bytes() const { return bytes_; }

QStandardItem *InformationElement::standard_item() const
{
	auto standard_item = new QStandardItem("Unknown IE");
	return standard_item;
}

QString InformationElement::summary() const { return ""; }

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
