#ifndef GUARD_H
#define GUARD_H

#include "employee.h"
#include <QListWidget>

class Guard : public Employee
{
public:
    Guard(int,std::string,Position,AttendanceLog, LeaveBalance);
    void _markAttendance(std::string);
    std::vector<std::string> _viewAttendance();

};

#endif // GUARD_H
