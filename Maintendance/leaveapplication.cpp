#include "leaveapplication.h"

LeaveApplication::LeaveApplication():employee(nullptr) {}

LeaveApplication::~LeaveApplication()
{
    delete employee;
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

