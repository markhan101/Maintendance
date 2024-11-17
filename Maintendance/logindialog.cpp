#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent),
                                            ui(new Ui::LoginDialog),
                                            loginPass()
{
    ui->setupUi(this);
    setWindowTitle("Login");
    if (parent)
    {
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

    if (_validateCredentials(username, password))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password!");
    }
}

bool LoginDialog::_validateCredentials(const QString &username, const QString &password)
{
    Position pos;
    if (loginPass.validateCredentials(username, password, pos))
    {
        userPosition = pos;
        userID = username.toInt();
        return true;
    }
    return false;
}