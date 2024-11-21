#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QDate>

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

QString _getPreDir(QString);

QString _getDateStr(QDate);

#endif // UTILS_H
