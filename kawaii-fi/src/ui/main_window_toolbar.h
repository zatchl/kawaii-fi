#ifndef MAIN_WINDOW_TOOL_BAR_H
#define MAIN_WINDOW_TOOL_BAR_H

#include <QByteArrayData>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QToolBar>

class QObject;
class QWidget;

class MainWindowToolbar : public QToolBar {
	Q_OBJECT
public:
	MainWindowToolbar(QWidget *parent = nullptr);
	void set_wireless_nics(const QStringList &wireless_nics);
	[[nodiscard]] QString current_wireless_nic() const;
	[[nodiscard]] int current_scan_interval() const;
	[[nodiscard]] bool scanning_enabled() const;

signals:
	void scanning_resumed(int scan_interval);
	void scanning_paused();

private:
	void add_spacer(int spacer_width);
	QPushButton *const scan_resume_pause_button_ = new QPushButton(this);
	QComboBox *const scan_interval_combo_box_ = new QComboBox(this);
	QLineEdit *const ap_filter_line_edit_ = new QLineEdit(this);
	QComboBox *const wireless_interface_combo_box_ = new QComboBox(this);
	bool scanning_enabled_ = true;
};

#endif // MAIN_WINDOW_TOOL_BAR_H
