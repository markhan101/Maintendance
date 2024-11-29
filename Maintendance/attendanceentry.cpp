#include "attendanceentry.h"


QString AttendanceEntry::_isPresent ()const
{
    return this->attendance;
}

QString AttendanceEntry::_getDate()const
{
    return this->attDate;
}

AttendanceEntry::AttendanceEntry(QString d, QString date, QString present, double hrs)
    : day(d), attDate(date), attendance(present), hours(hrs) {}
