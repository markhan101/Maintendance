#include "leaveapplication.h"

LeaveApplication::LeaveApplication():employee(nullptr) {}

LeaveApplication::~LeaveApplication()
{
    delete employee;
}


void LeaveApplication::apply()
{

}


void LeaveApplication::approve(std::string id)
{

}

void LeaveApplication::reject(std::string id)
{

}

std::string LeaveApplication::getStatus()const
{
    return this->status;
}
