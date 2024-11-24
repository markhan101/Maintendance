#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "employee.h"

struct PendingList
{
    QString AID;
    QString date;
};

class Supervisor : public Employee
{
public:
    Supervisor(QString, QString, Position, AttendanceLog*, LeaveBalance*);
    virtual ~Supervisor();

    QVector<PendingList>_getPendingList();

    void _approveOrRejectLeave(QString, bool);
    void _removePendingLeave(const QString& AID){
        for (int i = 0; i < pendingList.size(); ++i) {
            if (pendingList[i].AID == AID) {
                    pendingList.remove(i);
                    break;
                }
        }

    }





private:
    AttendanceLog* log;
    QVector<PendingList> pendingList;
};

#endif // SUPERVISOR_H
