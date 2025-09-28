#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog // Changed from QWidget to QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    bool isLoginSuccessful() const; // Method to check login status

private slots:
    void validateCredentials();

private:
    Ui::LoginDialog *ui;
    bool loginSuccessful; // Flag to track if login was successful
};

#endif // LOGINDIALOG_H
