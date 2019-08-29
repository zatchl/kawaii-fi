#ifndef POWER_CONSTRAINT_STANDARD_ITEM_H
#define POWER_CONSTRAINT_STANDARD_ITEM_H

#include <QStandardItem>
#include <libkawaii-fi/ies/power_constraint.h>

class PowerConstraintStandardItem : public QStandardItem {
public:
	PowerConstraintStandardItem(const PowerConstraint &power_constraint);
};

#endif // POWER_CONSTRAINT_STANDARD_ITEM_H
