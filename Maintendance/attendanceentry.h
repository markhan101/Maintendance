#ifndef ATTENDANCEENTRY_H
#define ATTENDANCEENTRY_H
#include <string>
#include <QString>
class AttendanceEntry
{
private:
    QString day;
    QString attDate;
    bool attendance;
    int hours = 8;

public:

    AttendanceEntry(QString d, QString date, bool present, int hrs = 8);
    QString _getDay() const { return day; }
    bool _isPresent() const;
    QString _getDate() const;
    int _getHours() const { return hours; }

};

#endif // ATTENDANCEENTRY_H
