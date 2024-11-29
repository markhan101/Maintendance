#ifndef ATTENDANCEENTRY_H
#define ATTENDANCEENTRY_H

#include <QString>
class AttendanceEntry
{
private:
    QString day;
    QString attDate;
    QString attendance;
    double hours;

public:

    AttendanceEntry(QString , QString , QString , double);
    QString _getDay() const { return day; }
    QString _isPresent() const;
    QString _getDate() const;
    double _getHours() const { return hours; }

};

#endif // ATTENDANCEENTRY_H
