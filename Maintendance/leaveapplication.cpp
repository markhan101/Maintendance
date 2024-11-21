#include "leaveapplication.h"

LeaveApplication::LeaveApplication(QString ID, LeaveTypes type, LeaveBalance* balance,QString fromDate,QString toDate, QString reason,QString genDate, QString status, int days):
    ID(ID), leaveType(type), balance(balance), fromDate(fromDate), toDate(toDate), reason(reason), applicationGeneratedDate(genDate), status(status),days(days){}


LeaveApplication::~LeaveApplication()
{

}


void LeaveApplication::apply()
{

}


void LeaveApplication::approve(QString id)
{

}

void LeaveApplication::reject(QString id)
{

}

QString LeaveApplication::getStatus()const
{
    return this->status;
}


bool LeaveApplication::handleCasualShortLeave()
{

}

