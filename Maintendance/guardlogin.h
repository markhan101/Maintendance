#ifndef GUARDLOGIN_H
#define GUARDLOGIN_H

#include <QWidget>
#include <QDialog>
#include "guard.h"
#include "markattendancescreen.h"

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

signals:
    void emitLogout();

private:
    Ui::GuardLogin *ui;
    MarkAttendanceScreen *markAttendance;
    Guard *currentGuard;
};

#endif // GUARDLOGIN_H
