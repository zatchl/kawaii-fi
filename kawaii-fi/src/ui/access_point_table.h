#ifndef ACCESS_POINT_TABLE_H
#define ACCESS_POINT_TABLE_H

#include "filter-menus/bssid_filter_menu.h"
#include "filter-menus/channel_filter_menu.h"
#include "filter-menus/channel_width_filter_menu.h"
#include "filter-menus/protocol_filter_menu.h"
#include "filter-menus/ssid_filter_menu.h"

#include <QAbstractTableModel>
#include <QSet>
#include <QSortFilterProxyModel>
#include <QString>
#include <QTableView>
#include <QVariant>
#include <QtCore>
#include <libkawaii-fi/access_point.h>
#include <libkawaii-fi/scanning/access_point_scanner.h>
#include <libkawaii-fi/standard.h>

class QWidget;

class AccessPointSortFilterProxyModel : public QSortFilterProxyModel {
	Q_OBJECT
public:
	explicit AccessPointSortFilterProxyModel(QObject *parent = nullptr);

	[[nodiscard]] bool filterAcceptsRow(int source_row,
	                                    const QModelIndex &source_parent) const override;

public slots:
	void set_acceptable_channels(QSet<unsigned int> acceptable_channels);
	void set_acceptable_channel_widths(QSet<unsigned int> acceptable_channel_widths);
	void set_acceptable_protocols(KawaiiFi::Standards acceptable_protocols);

private:
	QSet<unsigned int> acceptable_channels_;
	QSet<unsigned int> acceptable_channel_widths_;
	KawaiiFi::Standards acceptable_protocols_;
};

class AccessPointTableModel : public QAbstractTableModel {
	Q_OBJECT
public:
	explicit AccessPointTableModel(const KawaiiFi::Scanning::AccessPointScanner &ap_scanner,
	                               QObject *parent = nullptr);

	[[nodiscard]] int rowCount(const QModelIndex &parent) const override;
	[[nodiscard]] int columnCount(const QModelIndex &parent) const override;
	[[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
	[[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation,
	                                  int role) const override;

private:
	void refresh_model();
	const KawaiiFi::Scanning::AccessPointScanner &ap_scanner_;
};

class AccessPointTableView : public QTableView {
	Q_OBJECT
public:
	explicit AccessPointTableView(QWidget *parent = nullptr);
	explicit AccessPointTableView(const KawaiiFi::Scanning::AccessPointScanner &ap_scanner,
	                              QWidget *parent = nullptr);

	void set_ap_scanner(const KawaiiFi::Scanning::AccessPointScanner &ap_scanner);
	[[nodiscard]] AccessPointSortFilterProxyModel *ap_sort_filter_proxy_model();
	[[nodiscard]] SsidFilterMenu *ssid_filter_menu() const;
	[[nodiscard]] BssidFilterMenu *bssid_filter_menu() const;
	[[nodiscard]] ChannelFilterMenu *channel_filter_menu() const;
	[[nodiscard]] ChannelWidthFilterMenu *channel_width_filter_menu() const;
	[[nodiscard]] ProtocolFilterMenu *protocol_filter_menu() const;

signals:
	void access_point_selected(const QString &bssid);

private:
	void handle_item_selected(const QItemSelection &selected, const QItemSelection &deselected);
	void handle_header_context_menu_requested(const QPoint &point);
	AccessPointSortFilterProxyModel *const ap_sort_filter_proxy_model_ =
	        new AccessPointSortFilterProxyModel(this);
	SsidFilterMenu *const ssid_filter_menu_ = new SsidFilterMenu(this);
	BssidFilterMenu *const bssid_filter_menu_ = new BssidFilterMenu(this);
	ChannelFilterMenu *const channel_filter_menu_ = new ChannelFilterMenu(this);
	ChannelWidthFilterMenu *const channel_width_filter_menu_ = new ChannelWidthFilterMenu(this);
	ProtocolFilterMenu *const protocol_filter_menu_ = new ProtocolFilterMenu(this);
};

#endif // ACCESS_POINT_TABLE_H
