#ifndef ACCESS_POINT_STATUS_BAR_H
#define ACCESS_POINT_STATUS_BAR_H

#include <QByteArrayData>
#include <QLabel>
#include <QString>
#include <QWidget>

class QAction;
class QObject;

class AccessPointStatusBar : public QWidget {
	Q_OBJECT
public:
	AccessPointStatusBar(QAction *pause_action, QAction *resume_action, QWidget *parent = nullptr);

	void set_displayed_aps_status(unsigned int displayed_aps, unsigned int total_aps);

private:
	QLabel *const ap_status_label_ = new QLabel(this);
};

#endif // ACCESS_POINT_STATUS_BAR_H
