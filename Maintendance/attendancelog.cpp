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

    return true;
}

double AttendanceLog::_calculatePercentageForDateRange(const QDate& startDate, const QDate& endDate) const {
    double totalHours = 0;
    int workingDays = 0;

    for (const auto& entry : attEntries) {
        QDate entryDate = QDate::fromString(entry._getDate(), "yyyy/MM/dd");

        if (entryDate >= startDate && entryDate <= endDate) {
            // Count only weekdays (Monday to Friday)
            if (entryDate.dayOfWeek() <= 5) {
                workingDays++;
                totalHours += entry._getHours();
            }
        }
    }

    // Expected hours = workingDays * 8 hours
    double expectedHours = workingDays * 8.0;
    if (expectedHours == 0) return 0.0;

    // Calculate percentage (can be over 100%)
    return (totalHours / expectedHours) * 100.0;
}
double AttendanceLog::_getMonthlyAttendancePercentage(const QDate& date) const {
    QDate startOfMonth(date.year(), date.month(), 1);
    QDate endOfMonth(date.year(), date.month(), date.daysInMonth());

    return _calculatePercentageForDateRange(startOfMonth, endOfMonth);
}
double AttendanceLog::_getWeeklyAttendancePercentage(const QDate& date) const {

    QDate startOfWeek = date.addDays(-(date.dayOfWeek() - 1));

    QDate endOfWeek = startOfWeek.addDays(4);

    return _calculatePercentageForDateRange(startOfWeek, endOfWeek);
}





