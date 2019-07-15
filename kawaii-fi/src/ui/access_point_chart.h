#ifndef ACCESS_POINT_CHART_H
#define ACCESS_POINT_CHART_H

#include <QChart>
#include <Qt>
#include <libkawaii-fi/channel.h>

struct AccessPoint;

class QGraphicsItem;

class AccessPointChart : public QtCharts::QChart {
public:
	AccessPointChart(WifiBand band, QGraphicsItem *parent = nullptr,
	                 Qt::WindowFlags flags = Qt::WindowFlags());
	void add_access_point(const AccessPoint &ap);

private:
	void add_x_axis(WifiBand band);
	void add_y_axis();
};

#endif // ACCESS_POINT_CHART_H
