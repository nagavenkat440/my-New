#ifndef USBMONITOR_H
#define USBMONITOR_H

#include <QObject>
#include <QFileSystemWatcher>

class UsbMonitor : public QObject
{
    Q_OBJECT
public:
    explicit UsbMonitor(QObject *parent = nullptr);

signals:
    void deviceChanged();

private slots:
    void onUsbChanged(const QString &path);

private:
    QFileSystemWatcher watcher;
};

#endif // USBMONITOR_H
