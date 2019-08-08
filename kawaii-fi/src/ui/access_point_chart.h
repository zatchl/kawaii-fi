#ifndef ACCESS_POINT_CHART_H
#define ACCESS_POINT_CHART_H

#include <QByteArrayData>
#include <QChart>
#include <QColor>
#include <QString>
#include <Qt>
#include <libkawaii-fi/channel.h>

class AccessPoint;
class AccessPointScanner;
class QGraphicsItem;
class QObject;

class AccessPointChart : public QtCharts::QChart {
	Q_OBJECT
public:
	AccessPointChart(const AccessPointScanner &ap_scanner, WifiBand band,
	                 QGraphicsItem *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

private:
	void add_x_axis(WifiBand band);
	void add_y_axis();
	const AccessPointScanner &ap_scanner_;
	const WifiBand wifi_band_;

private slots:
	void refresh_chart();
	void add_access_point(const AccessPoint &ap, const QColor &color);
};

#endif // ACCESS_POINT_CHART_H
