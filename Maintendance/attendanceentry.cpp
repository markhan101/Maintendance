#include "attendanceentry.h"

AttendanceEntry::AttendanceEntry(std::string date, bool present, int hrs = 8):attDate(date), attendance(present), hours(hrs){}
bool AttendanceEntry::_isPresent ()const
{
    return this->attendance;
}

std::string AttendanceEntry::_getDate()const
{
    return this->attDate;
}
