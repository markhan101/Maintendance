#include "guard.h"

Guard::Guard(int ID, std::string name, Position pos, AttendanceLog att_log, LeaveBalance lb):
    Employee(ID, name, pos, att_log, lb)
{}

void Guard::_markAttendance(Employee* emp, std::string date, bool isPresent)
{

}

void Guard::_viewAttendance(int uID)
{
    //use the attendance balance to populate ui
}
