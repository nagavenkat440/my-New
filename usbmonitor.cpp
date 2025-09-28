#include "usbmonitor.h"

UsbMonitor::UsbMonitor(QObject *parent) : QObject(parent) {
    watcher.addPath("/dev"); // for Linux
    // watcher.addPath("E:/") // for Windows if needed
    connect(&watcher, &QFileSystemWatcher::directoryChanged,
            this, &UsbMonitor::onUsbChanged);
}

void UsbMonitor::onUsbChanged(const QString &) {
    emit deviceChanged();
}
