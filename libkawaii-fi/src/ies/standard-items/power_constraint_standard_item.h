#ifndef POWER_CONSTRAINT_STANDARD_ITEM_H
#define POWER_CONSTRAINT_STANDARD_ITEM_H

#include <QStandardItem>

namespace KawaiiFi::Ies {
	class PowerConstraint;
	class PowerConstraintStandardItem : public QStandardItem {
	public:
		explicit PowerConstraintStandardItem(const PowerConstraint &power_constraint);
	};
} // namespace KawaiiFi::Ies

#endif // POWER_CONSTRAINT_STANDARD_ITEM_H
