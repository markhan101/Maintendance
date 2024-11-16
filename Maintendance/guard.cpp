#include "guard.h"

Guard::Guard(int ID, std::string name, Position pos, AttendanceLog att_log, LeaveBalance lb):
    Employee(ID, name, pos, att_log, lb)
{}

void Guard::_markAttendance(std::string id)
{

}

std::vector<std::string> Guard::_viewAttendance()
{
    //use the attendance balance to populate ui
    std::vector<std::string> v1;
    v1.emplace_back("first item");
    v1.emplace_back("second item");
    v1.emplace_back("third item");
    v1.emplace_back("fourth item");

    return v1;

    //in actual we will return something like
    //return this->_getAttendanceRecord();
    //and for that we will have to change the return type or write multiple functions

}
