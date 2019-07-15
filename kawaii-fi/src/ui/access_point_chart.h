#ifndef ACCESS_POINT_CHART_H
#define ACCESS_POINT_CHART_H

#include <QChart>
#include <libkawaii-fi/channel.h>

class AccessPointChart : public QtCharts::QChart {
public:
	AccessPointChart(WifiBand band, QGraphicsItem *parent = nullptr,
	                 Qt::WindowFlags flags = Qt::WindowFlags());

private:
	void add_x_axis(WifiBand band);
	void add_y_axis();
};

#endif // ACCESS_POINT_CHART_H
