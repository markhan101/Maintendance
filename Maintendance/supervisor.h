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
    Supervisor(QString, QString, Position, AttendanceLog*, LeaveBalance*, bool);
    virtual ~Supervisor();

    virtual QVector<PendingList>_getPendingList();

    virtual void _approveOrRejectLeave(QString, bool);
    void _removePendingLeave(QString& AID){
        for (int i = 0; i < pendingList.size(); ++i) {
            if (pendingList[i].AID == AID) {
                    pendingList.remove(i);
                    break;
                }
        }

    }
    virtual void addtofile(const LeaveRecord& record, bool isApproved);

    virtual bool isDirector()
    {
        return false;
    }




private:
    AttendanceLog* log;
    QVector<PendingList> pendingList;
};

#endif // SUPERVISOR_H
