#include "employee.h"

Employee::Employee(int id, std::string name, Position position, AttendanceLog attlog, LeaveBalance leaveb):User(id,name), pos(position), attLog(attlog),leaveBalance(leaveb) {}

void Employee::_login()
{
    //nothing yet
}

void Employee::_logout()
{
    //same here
}

void Employee::_storeInfo()
{
    //add to file text
}

void Employee::_applyForLeave() {
    // Logic for applying for leave
}
std::vector<std::string> Employee::_viewAttendance(int uID) {
    // Logic for viewing attendance
}


std::vector<std::string>Employee::_viewAttendance() {
    // Logic for viewing attendance
}

void Employee::_getAttendanceRecord() {
    // Logic for getting attendance record
}

void Employee::_getLeaveBalance() {
    // Logic for getting leave balance
}
