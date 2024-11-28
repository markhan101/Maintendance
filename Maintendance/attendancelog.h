#ifndef ATTENDANCELOG_H
#define ATTENDANCELOG_H
#include <vector>
#include<QDate>
#include "attendanceentry.h"


class AttendanceLog
{
private:
    std::vector<AttendanceEntry> attEntries{};

public:
    AttendanceLog();
    void _addEntry(QString day, QString date, bool attendance, int hours); // Update declaration
    void _addEntry(AttendanceEntry &entry);
    void _displayEntries();
    double _getAttendancePercentage() const;
    std::vector<AttendanceEntry>& _getEntries() { return attEntries; }
    double _getMonthlyAttendancePercentage(const QDate& date) const;
    double _getWeeklyAttendancePercentage(const QDate& date) const;
    double _calculatePercentageForDateRange(const QDate& startDate, const QDate& endDate) const;

};

#endif // ATTENDANCELOG_H
