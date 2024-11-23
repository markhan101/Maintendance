#ifndef LEAVEAPPLICATION_H
#define LEAVEAPPLICATION_H


#include "utils.h"
#include "leavebalance.h"
#include <QDate>


struct LeaveRecord{
    QString ID;
    QString leaveType;
    QString fromDate;
    QString toDate;
    QString days;
    QString reason;
    QString status;
};

class LeaveApplication
{
private:
    QString ID;
    QString AID;
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
    LeaveApplication(QString,QString,LeaveTypes, LeaveBalance* ,QString , QString , QString , QString , QString , int );
    ~LeaveApplication();
    bool apply();
    
    QVector<LeaveRecord>* _readApprovedApplication(QString Id);
    QVector<LeaveRecord>* _readRejectedApplication(QString Id);

    
    QString getStatus()const;
    bool  handleCasualShortLeave();
    bool handleOtherLeaveTypes(LeaveTypes, int);
    QString _getId()
    {
        return ID;
    }
    QString FolderSelection(QString id);
};

#endif // LEAVEAPPLICATION_H
