#ifndef ATTENDANCELOG_H
#define ATTENDANCELOG_H
#include <vector>


#include "attendanceentry.h"
class AttendanceLog
{
private:
    std::vector<AttendanceEntry> attEntries{};

public:
    AttendanceLog();
    void _addEntry(std::string day, std::string date, bool attendance, int hours); // Update declaration
    void _addEntry(AttendanceEntry &entry);
    void _displayEntries();
    double _getAttendancePercentage() const;
    std::vector<AttendanceEntry>& _getEntries() { return attEntries; }
};

#endif // ATTENDANCELOG_H
