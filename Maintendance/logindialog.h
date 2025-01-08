#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include "utils.h"
#include "loginpass.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QParallelAnimationGroup>

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
    void setupTitleAnimation();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginDialog *ui;
    LoginPass loginPass;
    Position userPosition;
    QString userID;
    bool _validateCredentials(const QString& username, const QString& password);
    QPropertyAnimation *slideAnimation;
    QPropertyAnimation *fadeAnimation;
    QGraphicsOpacityEffect *opacityEffect;
};

#endif // LOGINDIALOG_H
