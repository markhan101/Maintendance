#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "user.h"
#include "attendancelog.h"
#include "leavebalance.h"
#include "utils.h"

class LeaveApplication;

class Employee : public User
{
private:
    Position pos;
    AttendanceLog attLog;
    LeaveBalance leaveBalance;

public:
    Employee();
    Employee(QString, QString, Position, AttendanceLog, LeaveBalance);

    void _login() override;
    void _logout() override;
    void _storeInfo() override;
    void _applyForLeave(LeaveApplication *);
    virtual AttendanceLog *_viewAttendance();
    //virtual std::vector<QString> _viewAttendance(QString);
    virtual void _getAttendanceRecord();
    virtual void _getLeaveBalance();
};

#endif // EMPLOYEE_H
