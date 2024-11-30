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
    Guard(QString,Position,AttendanceLog*, LeaveBalance*);
    bool _markAttendance(QString, AttendanceEntry*);
    virtual ~Guard();

private:
    AttendanceLog *log;
    bool _isAttendanceMarked(const QString& id, const QString& date);

};

#endif // GUARD_H
