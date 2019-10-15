#ifndef INFORMATION_ELEMENT_H
#define INFORMATION_ELEMENT_H

#include <QByteArray>
#include <QString>
#include <string_view>

class QStandardItem;

namespace KawaiiFi::Ies {
	class InformationElement {
	public:
		InformationElement(const std::string_view &bytes, unsigned int ie_id);

		InformationElement() = default;
		InformationElement(const InformationElement &ie) = default;
		InformationElement(InformationElement &&ie) = default;
		InformationElement &operator=(const InformationElement &ie) = delete;
		InformationElement &operator=(InformationElement &&ie) = delete;

		virtual ~InformationElement() = default;

		[[nodiscard]] const QByteArray &bytes() const;
		[[nodiscard]] unsigned int id() const;

		[[nodiscard]] virtual QStandardItem *standard_item() const;
		[[nodiscard]] virtual QString summary() const;

	protected:
		[[nodiscard]] bool bits_to_bool(QByteArray::size_type byte_index,
		                                unsigned int bit_index) const;
		[[nodiscard]] unsigned int bits_to_unsigned_int(QByteArray::size_type byte_index,
		                                                unsigned int bit_start_index,
		                                                unsigned int number_of_bits,
		                                                unsigned int default_value = 0) const;
		[[nodiscard]] unsigned int byte_to_unsigned_int(QByteArray::size_type byte_index,
		                                                unsigned int default_value = 0) const;

	private:
		const QByteArray bytes_;
		const unsigned int ie_id_ = 0;
	};
} // namespace KawaiiFi::Ies

#endif // INFORMATION_ELEMENT_H
