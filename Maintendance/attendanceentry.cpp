#include "attendanceentry.h"


bool AttendanceEntry::_isPresent ()const
{
    return this->attendance;
}

std::string AttendanceEntry::_getDate()const
{
    return this->attDate;
}

AttendanceEntry::AttendanceEntry(std::string d, std::string date, bool present, int hrs)
    : day(d), attDate(date), attendance(present), hours(hrs) {}
