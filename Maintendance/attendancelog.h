#ifndef ATTENDANCELOG_H
#define ATTENDANCELOG_H
#include <vector>
#include<QDate>
#include "attendanceentry.h"
#include <algorithm>


class AttendanceLog
{
private:
    std::vector<AttendanceEntry> attEntries{};

public:
    AttendanceLog();
    void _addEntry(QString day, QString date, QString attendance, int hours); // Update declaration
    void _addEntry(AttendanceEntry &entry);
    void _displayEntries();
    double _getAttendancePercentage() const;
    std::vector<AttendanceEntry>& _getEntries() { return attEntries; }
    double _getMonthlyAttendancePercentage(const QDate& date) const;
    double _getWeeklyAttendancePercentage(const QDate& date) const;
    double _calculatePercentageForDateRange(const QDate& startDate, const QDate& endDate) const;
    int _getSize()
    {
        return attEntries.size();
    }

};

#endif // ATTENDANCELOG_H
