#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "user.h"
#include "attendancelog.h"
#include "leavebalance.h"
#include "utils.h"
#include "leaveapplication.h"


class Employee: public User
{
private:
    Position pos;
    AttendanceLog log;
    LeaveBalance leaveBalance;

public:
    Employee(int ID, std::string name, Position pos, AttendanceLog att_log, LeaveBalance lb);
    virtual void _login () override;
    virtual void _logout () override;
    void _applyForLeave();
    virtual void _viewAttendance();
    virtual void _getAttendanceRecord();
    virtual void _getLeaveBalance();

};

#endif // EMPLOYEE_H
