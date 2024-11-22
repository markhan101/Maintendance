#ifndef LEAVEAPPLICATION_H
#define LEAVEAPPLICATION_H

#include "employee.h"
#include "utils.h"
#include <QDate>
//needs to be done still

class LeaveApplication
{
private:
    QString ID;
    LeaveTypes leaveType;
    LeaveBalance* balance;
    QString fromDate;
    QString toDate;
    QString reason;
    QString applicationGeneratedDate;
    QString status;
    int days;

    


public:
    LeaveApplication();
    LeaveApplication(QString,LeaveTypes, LeaveBalance* ,QString , QString , QString , QString , QString , int );
    ~LeaveApplication();
    bool apply();
    void approve(QString);
    void reject(QString);
    QString getStatus()const;
    bool  handleCasualShortLeave();
    bool handleOtherLeaveTypes(LeaveTypes, int);
    QString _getId(){
        return ID;
    }
    QString FolderSelection(QString id);
};

#endif // LEAVEAPPLICATION_H
