#ifndef ATTENDANCEENTRY_H
#define ATTENDANCEENTRY_H

#include <QString>
class AttendanceEntry
{
private:
    QString day;
    QString attDate;
    bool attendance;
    double hours;

public:

    AttendanceEntry(QString , QString , bool , double);
    QString _getDay() const { return day; }
    bool _isPresent() const;
    QString _getDate() const;
    int _getHours() const { return hours; }

};

#endif // ATTENDANCEENTRY_H
