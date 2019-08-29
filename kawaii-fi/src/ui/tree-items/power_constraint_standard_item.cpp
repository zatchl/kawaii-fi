#include "power_constraint_standard_item.h"

#include <QStandardItem>
#include <QString>
#include <libkawaii-fi/ies/power_constraint.h>

PowerConstraintStandardItem::PowerConstraintStandardItem(const PowerConstraint &power_constraint)
    : QStandardItem("Power Constraint")
{
	appendRow({new QStandardItem("Local Power Constraint"),
	           new QStandardItem(QString("%0 dB").arg(power_constraint.local_power_constraint()))});
}
