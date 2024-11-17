#include "attendancelog.h"

AttendanceLog::AttendanceLog() {}

void AttendanceLog::_addEntry(QString day, QString date, bool attendance, int hours)
{
    attEntries.emplace_back(day, date, attendance, hours);
}
//this function will recieve a pointer for the entry
void AttendanceLog::_addEntry(AttendanceEntry &entry)
{
    attEntries.emplace_back(entry);
}

void AttendanceLog::_displayEntries()
{
    //to be implemented and connected with Ui
}

double AttendanceLog::_getAttendancePercentage()const
{
    //to be implemented. make sure the entry class has an hours field
    //get clarity if this is attendance percentage in terms of hours or days?
    return true;
}



