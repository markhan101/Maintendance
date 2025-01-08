#ifndef DIRECTORLOGIN_H
#define DIRECTORLOGIN_H

#include <QWidget>
#include <QDialog>
#include <director.h>
#include "empattbysupdialogbox.h"
#include "pendingleavestable.h"
#include <QTimer>

namespace Ui {
class DirectorLogin;
}

class DirectorLogin : public QWidget
{
    Q_OBJECT

public:
    explicit DirectorLogin(QWidget *parent = nullptr);
    ~DirectorLogin();

    void _setDirector(Director * dir);

private:
    Ui::DirectorLogin *ui;
    Director * currentDir;

    QString fullMessage;
    int currentCharIndex;
    QTimer *typingTimer;
signals:
    void emitLogout();
private slots:
    void on_Logout_clicked();
    void on_viewEmpAttButton_clicked();
    void on_approveRejectButton_clicked();

    void updateWelcomeMessage();
};

#endif // DIRECTORLOGIN_H
