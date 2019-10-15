#ifndef STANDARD_H
#define STANDARD_H

#include <QFlag>
#include <QMetaType>
#include <QString>

namespace KawaiiFi {
	enum class Standard {
		B = 1 << 0,
		G = 1 << 1,
		N = 1 << 2,
		A = 1 << 3,
		AC = 1 << 4,
		AX = 1 << 5
	};

	Q_DECLARE_FLAGS(Standards, Standard)
	Q_DECLARE_OPERATORS_FOR_FLAGS(Standards)

	QString standard_to_string(Standard standard);

	QString standards_to_string(Standards standards, const QString &delimeter);
} // namespace KawaiiFi

Q_DECLARE_METATYPE(KawaiiFi::Standard)

#endif // STANDARD_H
