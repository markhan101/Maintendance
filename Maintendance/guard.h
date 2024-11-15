#ifndef GUARD_H
#define GUARD_H

#include "employee.h"

class Guard : public Employee
{
public:
    Guard(int,std::string,Position,AttendanceLog, LeaveBalance);
    void _markAttendance(std::string);
    void _viewAttendance(int);

};

#endif // GUARD_H
