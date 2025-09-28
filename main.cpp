#include "mainwindow.h"

#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<QVector<double>>(); // 2. Register it at run time
    // or: qRegisterMetaType<QVector<double>>("QVector<double>");

    LoginDialog loginDialog;
    // Run the login dialog modally
    if (loginDialog.exec() == QDialog::Accepted) { // Check if login was successful
        MainWindow w;
        w.show();
        return a.exec(); // Start the application event loop for the main window
    }
    // Exit if the login was not successful or was canceled
    return 0;
}
