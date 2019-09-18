#ifndef ACCESS_POINT_FILTER_MENU
#define ACCESS_POINT_FILTER_MENU

#include <QByteArrayData>
#include <QCheckBox>
#include <QMenu>
#include <QPushButton>
#include <QString>
#include <QVariant>
#include <QVector>

class QObject;
class QPoint;
class QWidget;

class FilterMenuCheckBox : public QCheckBox {
	Q_OBJECT
public:
	FilterMenuCheckBox(const QString &text, QVariant data, QWidget *parent = nullptr);
	[[nodiscard]] bool hitButton(const QPoint &pos) const override;
	[[nodiscard]] QVariant data() const;

private:
	const QVariant data_;
};

class AccessPointFilterMenu : public QMenu {
	Q_OBJECT
public:
	AccessPointFilterMenu(const QString &title, QWidget *parent = nullptr);
	void add_filter_check_box(QMenu *menu, const QString &text, const QVariant &data);
	void add_filter_check_box(const QString &text, const QVariant &data);

signals:
	void filter_changed();

protected:
	[[nodiscard]] QVector<FilterMenuCheckBox *> checked_filter_check_boxes() const;

private:
	QPushButton *select_all_button_ = new QPushButton("Select All", this);
	QVector<FilterMenuCheckBox *> filter_check_boxes_;
};

#endif // ACCESS_POINT_FILTER_MENU
