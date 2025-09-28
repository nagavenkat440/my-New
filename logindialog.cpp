#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QPixmap>
#include <QShortcut>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent), // Change QWidget to QDialog
    ui(new Ui::LoginDialog),
    loginSuccessful(false) // Initialize loginSuccessful
{
    ui->setupUi(this);

    // Connect the login button to the validateCredentials slot
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginDialog::validateCredentials);

    // Load and set the image
    QPixmap pixmap("FTU_Image.png");
    QPixmap scaledPixmap = pixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->imageLabel->setPixmap(scaledPixmap);
    ui->imageLabel->setScaledContents(false);

    // Set the password field to show stars
    ui->passwordEdit->setEchoMode(QLineEdit::Password);

    // Add Enter key shortcut
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(shortcut, &QShortcut::activated, ui->loginButton, &QPushButton::click);

    ui->usernameEdit->setPlaceholderText("User Name");
    ui->passwordEdit->setPlaceholderText("Password");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::validateCredentials() {
//    QString username = ui->usernameEdit->text();
//    QString password = ui->passwordEdit->text();

//    if (username == "admin" && password == "password") {
        loginSuccessful = true;  // Set the flag to indicate success
        accept();                // Signal success and close the dialog
//    } else {
//        QMessageBox::warning(this, "Login Failed", "Invalid username or password!");
//    }
}

bool LoginDialog::isLoginSuccessful() const {
    return loginSuccessful;
}



