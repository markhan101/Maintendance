#ifndef GUARD_H
#define GUARD_H

#include "employee.h"
#include "attendancelog.h"
#include <QListWidget>

class Guard : public Employee
{
public:
    Guard(int,std::string,Position,AttendanceLog, LeaveBalance);
    void _markAttendance(std::string, bool ispresent, int hours);
    AttendanceLog* _viewAttendance();

private:
    AttendanceLog *log;

};

#endif // GUARD_H
