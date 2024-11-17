#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include "utils.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    Position _getPosition() const { return userPosition; }
    QString _getUserID() const { return userID; }

private slots:
    void on_loginButton_clicked();

    //void on_usernameLineEdit_editingFinished();

private:
    Ui::LoginDialog *ui;
    Position userPosition;
    QString userID;
    bool _validateCredentials(const QString& username, const QString& password);
};

#endif
