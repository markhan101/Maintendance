#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "utils.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    Position getPosition() const { return userPosition; }
    int getUserID() const { return userID; }

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginDialog *ui;
    Position userPosition;
    int userID;
    bool validateCredentials(const QString& username, const QString& password);
};

#endif