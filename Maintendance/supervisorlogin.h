#ifndef SUPERVISORLOGIN_H
#define SUPERVISORLOGIN_H

#include <QWidget>
#include "viewattendance.h"
#include "supervisor.h"
#include "empattbysupdialogbox.h"
#include "pendingleavestable.h"
#include "director.h"

namespace Ui {
class SupervisorLogin;
}

class SupervisorLogin : public QWidget
{
    Q_OBJECT

public:
    explicit SupervisorLogin(QWidget *parent = nullptr);
    ~SupervisorLogin();
    void _setCurrentSup(Supervisor*);
    void _setCurrentDir(Director *);
    void _toggleButtons();

private slots:
    void on_logOutButton_clicked();

    void on_viewAttendanceButton_clicked();

    void on_viewEmployeeAttendanceButton_clicked();

    void on_approveRejectLeaveButton_clicked();

private:
    Ui::SupervisorLogin *ui;
    Supervisor * currentSup;
    Director * currentDir;


signals:
    void emitLogout();
};

#endif // SUPERVISORLOGIN_H
