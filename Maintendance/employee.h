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
    AttendanceLog attLog;
    LeaveBalance leaveBalance;

public:
    Employee();
    Employee(int, std::string, Position, AttendanceLog, LeaveBalance);

    void _login () override;
    void _logout () override;
    void _storeInfo() override;
    void _applyForLeave();
    virtual AttendanceLog* _viewAttendance();
    virtual std::vector<std::string> _viewAttendance(int);
    virtual void _getAttendanceRecord();
    virtual void _getLeaveBalance();

};

#endif // EMPLOYEE_H
