#ifndef STANDARD_H
#define STANDARD_H

#include "libkawaii-fi/channel.h"
#include "libkawaii-fi/ies/variant.h"

#include <QFlag>
#include <QMetaType>
#include <QString>
#include <QVector>

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

	Standards standards_from_ies(const QVector<Ies::Variant> &ies, Channel::Band band);
} // namespace KawaiiFi

Q_DECLARE_METATYPE(KawaiiFi::Standard)

#endif // STANDARD_H
