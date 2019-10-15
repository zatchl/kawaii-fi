#ifndef ACCESS_POINT_CHART_H
#define ACCESS_POINT_CHART_H

#include <QByteArrayData>
#include <QChart>
#include <QString>
#include <Qt>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/channel.h>
#include <libkawaii-fi/scanning/access_point_scanner.h>

class QGraphicsItem;
class QObject;

class AccessPointChart : public QtCharts::QChart {
	Q_OBJECT
public:
	AccessPointChart(const KawaiiFi::Scanning::AccessPointScanner &ap_scanner,
	                 KawaiiFi::Channel::Band band, QGraphicsItem *parent = nullptr,
	                 Qt::WindowFlags flags = Qt::WindowFlags());

private:
	void add_x_axis(KawaiiFi::Channel::Band band);
	void add_y_axis();
	const KawaiiFi::Scanning::AccessPointScanner &ap_scanner_;
	const KawaiiFi::Channel::Band wifi_band_;

private slots:
	void refresh_chart();
	void add_access_point(const KawaiiFi::AccessPoint &ap);
};

#endif // ACCESS_POINT_CHART_H
