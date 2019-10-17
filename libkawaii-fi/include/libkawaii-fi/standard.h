#ifndef STANDARD_H
#define STANDARD_H

#include <QFlag>
#include <QMetaType>
#include <QString>

namespace KawaiiFi {
	enum class Standard {
		B = 1U << 0U,
		G = 1U << 1U,
		N = 1U << 2U,
		A = 1U << 3U,
		AC = 1U << 4U,
		AX = 1U << 5U
	};

	Q_DECLARE_FLAGS(Standards, Standard)
	Q_DECLARE_OPERATORS_FOR_FLAGS(Standards)

	QString standard_to_string(Standard standard);

	QString standards_to_string(Standards standards, const QString &delimeter);
} // namespace KawaiiFi

Q_DECLARE_METATYPE(KawaiiFi::Standard)

#endif // STANDARD_H
