#ifndef LEAVEAPPLICATION_H
#define LEAVEAPPLICATION_H

#include "employee.h"
#include "utils.h"
#include <QDate>
//needs to be done still

class LeaveApplication
{
private:
    Employee *employee;
    LeaveTypes leaveType;
    QDate fromDate;
    QDate toDate;
    std::string reason;
    QDate applicationGeneratedDate;
    std::string status;

public:
    LeaveApplication();
    ~LeaveApplication();
    void apply();
    void approve(std::string);
    void reject(std::string);
    std::string getStatus()const;
};

#endif // LEAVEAPPLICATION_H
