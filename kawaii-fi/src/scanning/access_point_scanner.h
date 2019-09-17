#ifndef ACCESS_POINT_SCANNER_H
#define ACCESS_POINT_SCANNER_H

#include <NetworkManagerQt/ConnectionSettings>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QtCore>

class AccessPoint;
class WifiDevice;

class AccessPointScanner : public QObject {
	Q_OBJECT
public:
	explicit AccessPointScanner(QObject *parent = nullptr);

	void set_is_scanning(bool is_scanning);
	void set_wifi_device(const QString &device_name);
	void set_wifi_device(WifiDevice *wifi_device);

	[[nodiscard]] const QVector<AccessPoint> *access_points() const;
	[[nodiscard]] QStringList wifi_device_names() const;

signals:
	void access_points_changed(const QString &interface_name);

private:
	WifiDevice *selected_wifi_device_ = nullptr;
	QVector<WifiDevice *> wifi_devices_;
};

#endif // ACCESS_POINT_SCANNER_H
