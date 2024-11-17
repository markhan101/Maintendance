// logindialog.cpp
#include "logindialog.h"
#include "ui_logindialog.h"


LoginDialog::LoginDialog(QWidget *parent) : 
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowTitle("Login");
    if (parent) {
        resize(parent->size());
    }
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if(_validateCredentials(username, password)) {
        accept();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password!");
    }
}

bool LoginDialog::_validateCredentials(const QString& username, const QString& password)
{
    if(username == "guard" && password == "guard123") {
        userPosition = Position::guard;
        userID = "g1";
        return true;
    }
    else if(username == "employee" && password == "emp123") {
        userPosition = Position::normal_employee;
        userID = "e1";
        return true;
    }
    else if(username == "director" && password == "dir123") {
        userPosition = Position::director;
        userID = "s1";
        return true;
    }
    else
    return false;
}



