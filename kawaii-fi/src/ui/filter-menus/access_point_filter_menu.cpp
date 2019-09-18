#include "access_point_filter_menu.h"

#include <QAbstractButton>
#include <QCheckBox>
#include <QWidgetAction>
#include <QtCore>

class QWidget;

FilterMenuCheckBox::FilterMenuCheckBox(const QString &text, QVariant data, QWidget *parent)
    : QCheckBox(text, parent), data_(data)
{
	setCheckState(Qt::CheckState::Checked);
	setStyleSheet("padding: 2px 20px 2px 5px");
	setMaximumHeight(200);
}

bool FilterMenuCheckBox::hitButton(const QPoint &) const { return true; }

QVariant FilterMenuCheckBox::data() const { return data_; }

AccessPointFilterMenu::AccessPointFilterMenu(const QString &title, QWidget *parent)
    : QMenu(title, parent)
{
	select_all_button_->setFlat(true);
	connect(select_all_button_, &QPushButton::clicked, [this]() {
		for (const auto check_box : filter_check_boxes_) {
			check_box->blockSignals(true);
			check_box->setChecked(true);
			check_box->blockSignals(false);
		}
		emit filter_changed();
	});
	QWidgetAction *select_all_action = new QWidgetAction(this);
	select_all_action->setDefaultWidget(select_all_button_);
	addAction(select_all_action);
}

void AccessPointFilterMenu::add_filter_check_box(QMenu *menu, const QString &text, QVariant data)
{
	auto filter_check_box = new FilterMenuCheckBox(text, data, this);
	connect(filter_check_box, &QCheckBox::stateChanged, [this]() { emit filter_changed(); });
	filter_check_boxes_.append(filter_check_box);

	auto filter_action = new QWidgetAction(this);
	filter_action->setDefaultWidget(filter_check_box);
	menu->addAction(filter_action);
}

void AccessPointFilterMenu::add_filter_check_box(const QString &text, QVariant data)
{
	add_filter_check_box(this, text, data);
}

QVector<FilterMenuCheckBox *> AccessPointFilterMenu::checked_filter_check_boxes() const
{
	QVector<FilterMenuCheckBox *> checked_filter_check_boxes;
	for (const auto filter_check_box : filter_check_boxes_) {
		if (filter_check_box->isChecked()) {
			checked_filter_check_boxes.append(filter_check_box);
		}
	}
	return checked_filter_check_boxes;
}
