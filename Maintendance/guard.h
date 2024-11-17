#ifndef GUARD_H
#define GUARD_H


#include <QListWidget>
#include <QStandardPaths>
#include <iostream>
#include <QFile>
#include <QDateTime>
#include<QDate>
#include <QString>

#include <QTextStream>
#include <QCoreApplication>
#include <QDir>
#include "employee.h"
#include "attendancelog.h"

class Guard : public Employee
{
public:
    Guard(int,std::string,Position,AttendanceLog, LeaveBalance);
    void _markAttendance(std::string, bool , QDate,int  );
    AttendanceLog* _viewAttendance();

private:
    AttendanceLog *log;

};

#endif // GUARD_H
