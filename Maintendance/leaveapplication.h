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
    LeaveBalance* balance;

    QString fromDate;
    QString toDate;
    QString reason;
    QDate applicationGeneratedDate;
    QString status;
    int days;

    


public:
    LeaveApplication();
    LeaveApplication(QString fromDate, QString toDate, QString reason, QDate applicationGeneratedDate, QString status, int days);
    ~LeaveApplication();
    void apply();
    void approve(QString);
    void reject(QString);
    QString getStatus()const;
    bool  handleCasualShortLeave(int daysRequested, LeaveBalance *balance);
};

#endif // LEAVEAPPLICATION_H
