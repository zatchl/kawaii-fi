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

class AccessPointScanner;
class QWidget;

class AccessPointSortFilterProxyModel : public QSortFilterProxyModel {
	Q_OBJECT
public:
	AccessPointSortFilterProxyModel(QObject *parent = nullptr);

	[[nodiscard]] bool filterAcceptsRow(int source_row,
	                                    const QModelIndex &source_parent) const override;

public slots:
	void set_acceptable_channels(QSet<unsigned int> acceptable_channels);
	void set_acceptable_channel_widths(QSet<unsigned int> acceptable_channel_widths);
	void set_acceptable_protocols(QSet<Protocol> acceptable_protocols);

private:
	QSet<unsigned int> acceptable_channels_;
	QSet<unsigned int> acceptable_channel_widths_;
	QSet<Protocol> acceptable_protocols_;
};

class AccessPointTableModel : public QAbstractTableModel {
	Q_OBJECT
public:
	AccessPointTableModel(const AccessPointScanner &ap_scanner, QObject *parent = nullptr);

	[[nodiscard]] int rowCount(const QModelIndex &parent) const override;
	[[nodiscard]] int columnCount(const QModelIndex &parent) const override;
	[[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
	[[nodiscard]] QVariant headerData(int section, Qt::Orientation, int role) const override;

private:
	void refresh_model();
	const AccessPointScanner &ap_scanner_;
};

class AccessPointTableView : public QTableView {
	Q_OBJECT
public:
	AccessPointTableView(QWidget *parent = nullptr);
	AccessPointTableView(const AccessPointScanner &ap_scanner, QWidget *parent = nullptr);

	void set_ap_scanner(const AccessPointScanner &ap_scanner);
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
