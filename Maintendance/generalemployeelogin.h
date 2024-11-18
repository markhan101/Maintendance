#ifndef GENERALEMPLOYEELOGIN_H
#define GENERALEMPLOYEELOGIN_H

#include <QWidget>
#include "employee.h"
#include "viewattendance.h"

namespace Ui {
class GeneralEmployeeLogin;
}

class GeneralEmployeeLogin : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralEmployeeLogin(QWidget *parent = nullptr);
    ~GeneralEmployeeLogin();
    void _setEmployee(Employee*);

private:
    Ui::GeneralEmployeeLogin *ui;
    Employee *generalEmp;


signals:
    void emitLogout();
private slots:
    void on_logoutButton_clicked();
    void on_viewAttendanceButton_clicked();
};

#endif // GENERALEMPLOYEELOGIN_H
