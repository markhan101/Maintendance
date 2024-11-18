#ifndef EMPLOYEE_H
#define EMPLOYEE_H

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

#include "attendancelog.h"
#include "user.h"
#include "leavebalance.h"
#include "utils.h"

class LeaveApplication;

class Employee : public User
{
private:
    Position pos;
    AttendanceLog *attLog;
    LeaveBalance leaveBalance;

public:
    Employee();
    Employee(QString, QString, Position, AttendanceLog*, LeaveBalance);

    virtual ~Employee();
    void _applyForLeave(LeaveApplication *);
    AttendanceLog *_viewAttendance();
   // virtual AttendanceLog *_viewAttendance(QString);
    virtual void _getAttendanceRecord();
    virtual void _getLeaveBalance();
};

#endif // EMPLOYEE_H
