#include "main_window_toolbar.h"

#include <QAbstractButton>
#include <QMap>
#include <QSizePolicy>
#include <QStyle>
#include <QToolBar>
#include <QWidget>
#include <QtCore>

namespace {
	const QMap<QString, int> scan_interval_map = {{QT_TR_NOOP("10 seconds"), 10},
	                                              {QT_TR_NOOP("30 seconds"), 30},
	                                              {QT_TR_NOOP("60 seconds"), 60}};
	const int toolbar_bottom_margin = 5;
	const int toolbar_widget_spacing = 5;
} // namespace

MainWindowToolbar::MainWindowToolbar(QWidget *parent) : QToolBar(parent)
{
	scan_resume_pause_button_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	scan_resume_pause_button_->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
	connect(scan_resume_pause_button_, &QPushButton::clicked, [this]() {
		scanning_enabled_ = !scanning_enabled_;
		if (scanning_enabled_) {
			scan_resume_pause_button_->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
			emit scanning_resumed(current_scan_interval());
		} else {
			scan_resume_pause_button_->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
			emit scanning_paused();
		}
	});

	scan_interval_combo_box_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	scan_interval_combo_box_->addItems(scan_interval_map.keys());
	connect(scan_interval_combo_box_, &QComboBox::currentTextChanged, [this]() {
		if (scanning_enabled_) {
			emit scanning_resumed(current_scan_interval());
		}
	});

	ap_filter_line_edit_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	ap_filter_line_edit_->setPlaceholderText(tr("Add filter..."));

	wireless_interface_combo_box_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	setMovable(false);
	setContentsMargins(0, 0, 0, toolbar_bottom_margin);
	addWidget(scan_resume_pause_button_);
	add_spacer(toolbar_widget_spacing);
	addWidget(scan_interval_combo_box_);
	add_spacer(toolbar_widget_spacing);
	addWidget(ap_filter_line_edit_);
	add_spacer(toolbar_widget_spacing);
	addWidget(wireless_interface_combo_box_);
}

void MainWindowToolbar::set_wireless_nics(const QStringList &wireless_nics)
{
	wireless_interface_combo_box_->clear();
	for (const QString &nic : wireless_nics) {
		wireless_interface_combo_box_->addItem(nic);
	}
	wireless_interface_combo_box_->setCurrentIndex(0);
}

QString MainWindowToolbar::current_wireless_nic() const
{
	return wireless_interface_combo_box_->currentText();
}

int MainWindowToolbar::current_scan_interval() const
{
	return scan_interval_map[scan_interval_combo_box_->currentText()];
}

bool MainWindowToolbar::scanning_enabled() const { return scanning_enabled_; }

void MainWindowToolbar::add_spacer(int spacer_width)
{
	auto spacer = new QWidget(this);
	spacer->setFixedWidth(spacer_width);
	this->addWidget(spacer);
}
