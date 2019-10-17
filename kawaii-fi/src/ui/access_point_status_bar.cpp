#include "access_point_status_bar.h"

#include <QAbstractButton>
#include <QAction>
#include <QHBoxLayout>
#include <QPushButton>
#include <QString>
#include <QStyle>
#include <Qt>
#include <utility>

AccessPointStatusBar::AccessPointStatusBar(QAction *pause_action, QAction *resume_action,
                                           QWidget *parent)
    : QWidget(parent)
{
	auto scan_toggle_button = new QPushButton(this);
	scan_toggle_button->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
	scan_toggle_button->setFlat(true);
	scan_toggle_button->setFocusPolicy(Qt::FocusPolicy::NoFocus);

	auto layout = new QHBoxLayout();
	layout->setMargin(1);
	layout->addWidget(ap_status_label_);
	layout->addWidget(scan_toggle_button);
	setLayout(layout);

	// Trigger either the pause or resume actions depending on which one is enabled
	connect(scan_toggle_button, &QPushButton::clicked, [pause_action, resume_action]() {
		if ((pause_action != nullptr) && pause_action->isEnabled()) {
			pause_action->trigger();
		} else if ((resume_action != nullptr) && resume_action->isEnabled()) {
			resume_action->trigger();
		}
	});

	// Change the icon of the scan toggle button when the pause or resume actions are triggered
	connect(pause_action, &QAction::triggered, [scan_toggle_button, this]() {
		scan_toggle_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	});
	connect(resume_action, &QAction::triggered, [scan_toggle_button, this]() {
		scan_toggle_button->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
	});
}

void AccessPointStatusBar::set_displayed_aps_status(unsigned int displayed_aps,
                                                    unsigned int total_aps)
{
	ap_status_label_->setText(
	        QString("Displaying %0/%1 Access Points").arg(displayed_aps).arg(total_aps));
}
