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
    QString reason;
    QDate applicationGeneratedDate;
    QString status;

public:
    LeaveApplication();
    ~LeaveApplication();
    void apply();
    void approve(QString);
    void reject(QString);
    QString getStatus()const;
};

#endif // LEAVEAPPLICATION_H
