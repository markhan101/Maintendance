#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "user.h"
#include "attendancelog.h"
#include "leavebalance.h"
#include "utils.h"



class Employee: public User
{
private:
    Position pos;
    AttendanceLog log;
    LeaveBalance leaveBalance;

public:
    Employee();
    Employee(int ID, std::string name, Position pos, AttendanceLog att_log, LeaveBalance lb);

    void _login () override;
    void _logout () override;
    void _applyForLeave();
    virtual void _viewAttendance();
    virtual void _getAttendanceRecord();
    virtual void _getLeaveBalance();

};

#endif // EMPLOYEE_H
