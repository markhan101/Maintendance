#include "attendanceentry.h"

/**
 * Gets the attendance status of the employee
 * @return QString representing whether the employee was present/absent
 */
QString AttendanceEntry::_isPresent() const
{
    return this->attendance;
}

/**
 * Gets the date for this attendance record
 * @return QString containing the date of the attendance entry
 */
QString AttendanceEntry::_getDate() const
{
    return this->attDate;
}

/**
 * Constructor for creating a new attendance entry
 * @param d The day of the week (e.g., "Monday", "Tuesday")
 * @param date The full date of the attendance record
 * @param present The attendance status (e.g., "Present", "Absent")
 * @param hrs Number of hours worked, if applicable
 */
AttendanceEntry::AttendanceEntry(QString d, QString date, QString present, double hrs)
    : day(d), attDate(date), attendance(present), hours(hrs) {}
