#ifndef ATTENDANCEENTRY_H
#define ATTENDANCEENTRY_H
#include <string>
class AttendanceEntry
{
private:
    std::string attDate;
    bool attendance;
    int hours = 8;

public:

    AttendanceEntry(std::string, bool, int);

    bool _isPresent()const;
    std::string _getDate() const;
    int _getHours() const { return hours; }

};

#endif // ATTENDANCEENTRY_H
