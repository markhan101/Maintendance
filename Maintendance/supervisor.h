#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "employee.h"

class Supervisor : public Employee
{
public:
    Supervisor(QString,QString,Position,AttendanceLog*, LeaveBalance);
    virtual ~Supervisor();

private:
    AttendanceLog* log;
};

#endif // SUPERVISOR_H
