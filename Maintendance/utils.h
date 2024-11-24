#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QDate>
#include <QUuid>
#include <QCoreApplication>
#include <QFile>
#include <QDir>


enum LeaveTypes
{
    Casual = 0,
    Earned = 1,
    Official = 2,
    Unpaid = 3
};

enum Position
{
    none = -1,
    guard = 0,
    normal_employee = 1,
    supervisor = 2,
    director = 3
};

struct LeaveRecord
{
    QString ID;
    QString leaveType;
    QString fromDate;
    QString toDate;
    QString days;
    QString reason;
    QString status;
};




QString _getPreDir(QString);

QString _getDateStr(QDate);

bool _sanitizeInput(QString);

QString _generateApplicationID(QString);

LeaveRecord _getRecord(QString);

QString FolderSelection(QString);

QString _getPosStr(int);

#endif // UTILS_H
