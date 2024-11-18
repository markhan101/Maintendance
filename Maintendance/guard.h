#ifndef GUARD_H
#define GUARD_H


#include <QListWidget>
#include <QStandardPaths>
#include <QFile>
#include <QDateTime>
#include <QDate>
#include <QString>
#include <QTextStream>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>

#include "employee.h"
#include "attendancelog.h"


class Guard : public Employee
{
public:
    Guard(QString,QString,Position,AttendanceLog*, LeaveBalance);
    bool _markAttendance(QString, AttendanceEntry*);
    virtual ~Guard();

private:
    AttendanceLog *log;

};

#endif // GUARD_H
