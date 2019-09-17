#ifndef POWER_CONSTRAINT_STANDARD_ITEM_H
#define POWER_CONSTRAINT_STANDARD_ITEM_H

#include <QStandardItem>

class PowerConstraint;

class PowerConstraintStandardItem : public QStandardItem {
public:
	explicit PowerConstraintStandardItem(const PowerConstraint &power_constraint);
};

#endif // POWER_CONSTRAINT_STANDARD_ITEM_H
