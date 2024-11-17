#ifndef ATTENDANCEENTRY_H
#define ATTENDANCEENTRY_H
#include <string>
class AttendanceEntry
{
private:
    std::string day;
    std::string attDate;
    bool attendance;
    int hours = 8;

public:

    AttendanceEntry(std::string d, std::string date, bool present, int hrs = 8);
    std::string _getDay() const { return day; }
    bool _isPresent() const;
    std::string _getDate() const;
    int _getHours() const { return hours; }

};

#endif // ATTENDANCEENTRY_H
