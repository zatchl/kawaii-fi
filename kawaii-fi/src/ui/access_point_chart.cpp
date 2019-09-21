#include "access_point_chart.h"

#include "scanning/access_point_scanner.h"

#include <QCategoryAxis>
#include <QGraphicsLayout>
#include <QHashNode>
#include <QLegend>
#include <QLineSeries>
#include <QList>
#include <QMargins>
#include <QPen>
#include <QString>
#include <QValueAxis>
#include <QVector>
#include <QtGui>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/channel.h>
#include <libkawaii-fi/util.h>

class QGraphicsItem;

namespace {
	const int min_signal_dbm = -100;
	const int max_signal_dbm = -20;
	const int y_axis_ticks = ((max_signal_dbm - min_signal_dbm) / 10) + 1;

	const unsigned int two_point_four_ghz_x_min = 2400;
	const unsigned int two_point_four_ghz_x_max = 2496;
	const QVector<unsigned int> two_point_four_ghz_x_freqs = {
	        2412, 2417, 2422, 2427, 2432, 2437, 2442, 2447, 2452, 2457, 2462, 2467, 2472, 2484};

	const unsigned int five_ghz_x_min = 5150;
	const unsigned int five_ghz_x_max = 5875;
	const QVector<unsigned int> five_ghz_x_freqs = {
	        5180, 5200, 5220, 5240, 5260, 5280, 5300, 5320, 5500, 5520, 5540, 5560, 5580,
	        5600, 5620, 5640, 5660, 5680, 5700, 5720, 5745, 5765, 5785, 5805, 5825};

	const int series_line_width = 3;
} // namespace

AccessPointChart::AccessPointChart(const AccessPointScanner &ap_scanner, WifiBand band,
                                   QGraphicsItem *parent, Qt::WindowFlags flags)
    : QtCharts::QChart(parent, flags), ap_scanner_(ap_scanner), wifi_band_(band)
{
	connect(&ap_scanner, &AccessPointScanner::access_points_changed, this,
	        &AccessPointChart::refresh_chart);
	legend()->setVisible(false);
	setMargins(QMargins(0, 0, 0, 0));
	layout()->setContentsMargins(0, 0, 0, 0);
	add_x_axis(band);
	add_y_axis();
}

void AccessPointChart::add_x_axis(WifiBand band)
{
	if ((band != WifiBand::TwoPointFourGhz) && (band != WifiBand::FiveGhz)) {
		return;
	}

	auto *x_axis = new QtCharts::QCategoryAxis(this);
	x_axis->setTitleText(tr("Channel"));
	x_axis->setGridLineVisible(false);
	x_axis->setLabelsPosition(QtCharts::QCategoryAxis::AxisLabelsPositionOnValue);

	// Use different values for the x-axis depending on the band of the access points to be charted
	const int x_axis_min =
	        (band == WifiBand::TwoPointFourGhz) ? two_point_four_ghz_x_min : five_ghz_x_min;
	const int x_axis_max =
	        (band == WifiBand::TwoPointFourGhz) ? two_point_four_ghz_x_max : five_ghz_x_max;
	const QVector<unsigned int> &x_freqs =
	        (band == WifiBand::TwoPointFourGhz) ? two_point_four_ghz_x_freqs : five_ghz_x_freqs;

	x_axis->setMin(x_axis_min);
	x_axis->setMax(x_axis_max);
	for (auto freq : x_freqs) {
		x_axis->append(QString::number(ieee80211_frequency_to_channel(freq)), freq);
	}

	addAxis(x_axis, Qt::AlignBottom);
}

void AccessPointChart::add_y_axis()
{
	auto *y_axis = new QtCharts::QValueAxis(this);
	y_axis->setTitleText(tr("Signal (dBm)"));
	y_axis->setGridLineVisible(false);
	y_axis->setLabelFormat("%i");
	y_axis->setRange(min_signal_dbm, max_signal_dbm);
	y_axis->setTickCount(y_axis_ticks);

	addAxis(y_axis, Qt::AlignLeft);
}

void AccessPointChart::refresh_chart()
{
	removeAllSeries();

	const QVector<AccessPoint> *access_points = ap_scanner_.access_points();

	if (access_points) {
		for (const auto &ap : *access_points) {
			add_access_point(ap);
		}
	}
}

void AccessPointChart::add_access_point(const AccessPoint &ap)
{
	const Channel channel = ap.channel();

	if (channel.band() != wifi_band_) {
		return;
	}

	auto *series = new QtCharts::QLineSeries(this);
	series->setName(ap.bssid());
	series->setPen(QPen(QBrush(ap.color()), series_line_width));
	series->append(channel.start_mhz(), min_signal_dbm);
	series->append(channel.start_mhz(), ap.signal_dbm());
	series->append(channel.end_mhz(), ap.signal_dbm());
	series->append(channel.end_mhz(), min_signal_dbm);
	if (channel.width() == ChannelWidth::EightyPlusEightyMhz) {
		series->append(channel.start_mhz_two(), min_signal_dbm);
		series->append(channel.start_mhz_two(), ap.signal_dbm());
		series->append(channel.end_mhz_two(), ap.signal_dbm());
		series->append(channel.end_mhz_two(), min_signal_dbm);
	}
	addSeries(series);
	const auto xy_axes = axes();
	for (const auto axis : xy_axes) {
		series->attachAxis(axis);
	}
}
