#ifndef GUARDLOGIN_H
#define GUARDLOGIN_H

#include <QWidget>
#include <QDialog>
#include "guard.h"
#include "markattendancescreen.h"
#include "viewattendance.h"
#include <leaveapplicationform.h>

namespace Ui {
class GuardLogin;
}

class GuardLogin : public QWidget
{
    Q_OBJECT

public:
    explicit GuardLogin(QWidget *parent = nullptr);
    ~GuardLogin();

    void setCurrentGuard(Guard *guard); // Setter for currentGuard

private slots:
    void on_markAttendanceButton_clicked(); // No arguments in slot
    void on_logOutButton_clicked();

    void on_viewAttendanceButton_clicked();
    void on_requestLeaveButton_clicked();

signals:
    void emitLogout();

private:
    Ui::GuardLogin *ui;
    Guard *currentGuard;
};

#endif // GUARDLOGIN_H
