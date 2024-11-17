#include "employee.h"

Employee::Employee(QString id, QString name, Position position, AttendanceLog attlog, LeaveBalance leaveb):User(id,name), pos(position), attLog(attlog),leaveBalance(leaveb) {}

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

void Employee::_applyForLeave(LeaveApplication *application) {
    // Logic for applying for leave
}
//std::vector<QString> Employee::_viewAttendance(QString uID) {
    // Logic for viewing attendance
//}


AttendanceLog* Employee::_viewAttendance( ) {
    // Logic for viewing attendance
}

void Employee::_getAttendanceRecord() {
    // Logic for getting attendance record
}

void Employee::_getLeaveBalance() {
    // Logic for getting leave balance
}
