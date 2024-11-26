#ifndef GENERALEMPLOYEELOGIN_H
#define GENERALEMPLOYEELOGIN_H

#include <QWidget>
#include "employee.h"
#include "viewattendance.h"
#include "leaveapplicationform.h"

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
    void on_viewLeaveBalanceButton_clicked();
    void on_requestLeaveButton_clicked();
       void displayAttendancePercentages() {
        if (!generalEmp) return;
        
        AttendanceLog* log = generalEmp->_viewAttendance();
        QDate currentDate = QDate::currentDate();
        
        double monthlyPercentage = log->_getMonthlyAttendancePercentage(currentDate);
        double weeklyPercentage = log->_getWeeklyAttendancePercentage(currentDate);
        
        QString message = QString("Attendance Statistics:\n\n"
                                "Monthly Attendance: %1%\n"
                                "Weekly Attendance: %2%")
                                .arg(monthlyPercentage, 0, 'f', 2)
                                .arg(weeklyPercentage, 0, 'f', 2);
        
        QMessageBox::information(this, "Attendance Percentages", message);
        
        delete log;
    }
};

#endif // GENERALEMPLOYEELOGIN_H
