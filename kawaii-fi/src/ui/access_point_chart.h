#ifndef ACCESS_POINT_CHART_H
#define ACCESS_POINT_CHART_H

#include <QByteArrayData>
#include <QChart>
#include <QColor>
#include <QString>
#include <Qt>
#include <libkawaii-fi/channel.h>

class QAbstractItemModel;
class QGraphicsItem;
class QObject;

class AccessPointChart : public QtCharts::QChart {
	Q_OBJECT
public:
	AccessPointChart(WifiBand band, QGraphicsItem *parent = nullptr,
	                 Qt::WindowFlags flags = Qt::WindowFlags());
	void set_model(QAbstractItemModel *ap_model);

private:
	void add_x_axis(WifiBand band);
	void add_y_axis();
	QAbstractItemModel *ap_model_ = nullptr;
	const WifiBand wifi_band_;

private slots:
	void update_access_points();
	void add_access_point(const QString &bssid, const QColor &color, const Channel &channel,
	                      double signal_dbm);
};

#endif // ACCESS_POINT_CHART_H
