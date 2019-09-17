#ifndef INFORMATION_ELEMENT_H
#define INFORMATION_ELEMENT_H

#include <QByteArray>
#include <QMetaType>

class QStandardItem;

class InformationElement {
public:
	InformationElement() = default;
	InformationElement(const QByteArray &bytes);
	InformationElement(const char *bytes, int size);
	InformationElement(const InformationElement &ie) = default;
	InformationElement(InformationElement &&ie) = default;
	virtual ~InformationElement() = default;
	InformationElement &operator=(const InformationElement &ie) = default;
	InformationElement &operator=(InformationElement &&ie) = default;
	[[nodiscard]] const QByteArray &bytes() const;
	[[nodiscard]] QByteArray &bytes();

	// Marshall the information element data into a D-Bus argument
	friend QDBusArgument &operator<<(QDBusArgument &argument, const InformationElement &ie);
	[[nodiscard]] virtual QStandardItem *standard_item() const;
	[[nodiscard]] virtual QString summary() const;

	// Retrive the information element data from the D-Bus argument
	friend const QDBusArgument &operator>>(const QDBusArgument &argument, InformationElement &ie);
protected:
	[[nodiscard]] bool bits_to_bool(QByteArray::size_type byte_index, unsigned int bit_index) const;
	[[nodiscard]] unsigned int bits_to_unsigned_int(QByteArray::size_type byte_index,
	                                                unsigned int bit_start_index,
	                                                unsigned int number_of_bits,
	                                                unsigned int default_value = 0) const;
	[[nodiscard]] unsigned int byte_to_unsigned_int(QByteArray::size_type byte_index,
	                                                unsigned int default_value = 0) const;

private:
	QByteArray bytes_;
};
Q_DECLARE_METATYPE(InformationElement)

#endif // INFORMATION_ELEMENT_H
