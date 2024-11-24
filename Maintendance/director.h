#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "employee.h"

struct PendingList
{
    QString AID;
    QString date;
};

class Director : public Employee
{
public:
    Director(QString, QString, Position, AttendanceLog*, LeaveBalance*);
    virtual ~Director();

    QVector<PendingList>_getPendingList();

    void _approveOrRejectLeave(QString, bool);
    void _removePendingLeave(QString& AID){
        for (int i = 0; i < pendingList.size(); ++i) {
            if (pendingList[i].AID == AID) {
                pendingList.remove(i);
                break;
            }
        }

    }
    void addtofile(const LeaveRecord& record, bool isApproved);





private:
    AttendanceLog* log;
    QVector<PendingList> pendingList;
};

#endif
