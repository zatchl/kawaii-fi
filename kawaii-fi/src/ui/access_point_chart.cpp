#include "access_point_chart.h"

#include <QCategoryAxis>
#include <QLineSeries>
#include <QValueAxis>
#include <QVector>
#include <libkawaii-fi/util.h>

namespace {
	const int min_signal_dbm = -100;
	const int max_signal_dbm = -20;
	const int y_axis_ticks = ((max_signal_dbm - min_signal_dbm) / 10) + 1;
} // namespace

AccessPointChart::AccessPointChart(WifiBand band, QGraphicsItem *parent, Qt::WindowFlags flags)
    : QtCharts::QChart(parent, flags)
{
	legend()->setVisible(false);
	setMargins(QMargins(0, 0, 0, 0));
	add_x_axis(band);
	add_y_axis();
}

void AccessPointChart::add_access_point(const AccessPoint &ap)
{
	const Channel channel = ap.channel();
	auto *series = new QtCharts::QLineSeries(this);
	series->append(channel.start_mhz(), min_signal_dbm);
	series->append(channel.start_mhz(), ap.signal_strength_dbm());
	series->append(channel.end_mhz(), ap.signal_strength_dbm());
	series->append(channel.end_mhz(), min_signal_dbm);
	if (channel.width() == ChannelWidth::EightyPlusEightyMhz) {
		series->append(channel.start_mhz_two(), min_signal_dbm);
		series->append(channel.start_mhz_two(), ap.signal_strength_dbm());
		series->append(channel.end_mhz_two(), ap.signal_strength_dbm());
		series->append(channel.end_mhz_two(), min_signal_dbm);
	}
	addSeries(series);
	for (const auto axis : axes()) {
		series->attachAxis(axis);
	}
}

void AccessPointChart::add_x_axis(WifiBand band)
{
	auto *x_axis = new QtCharts::QCategoryAxis(this);
	x_axis->setTitleText(tr("Channel"));
	x_axis->setGridLineVisible(false);
	x_axis->setLabelsPosition(QtCharts::QCategoryAxis::AxisLabelsPositionOnValue);
	int x_axis_min = 0;
	int x_axis_max = 0;
	QVector<int> x_freqs;
	switch (band) {
	case Band::TwoPointFourGhz:
		x_axis_min = 2400;
		x_axis_max = 2496;
		x_freqs = {2412, 2417, 2422, 2427, 2432, 2437, 2442,
		           2447, 2452, 2457, 2462, 2467, 2472, 2484};
		break;
	case Band::FiveGhz:
		x_axis_min = 5150;
		x_axis_max = 5875;
		x_freqs = {5180, 5200, 5220, 5240, 5260, 5280, 5300, 5320, 5500, 5520, 5540, 5560, 5580,
		           5600, 5620, 5640, 5660, 5680, 5700, 5720, 5745, 5765, 5785, 5805, 5825};
		break;
	default:
		break;
	}
	x_axis->setMin(x_axis_min);
	x_axis->setMax(x_axis_max);
	for (int freq : x_freqs) {
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
