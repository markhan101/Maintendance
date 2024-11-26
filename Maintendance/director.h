#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "supervisor.h"

class Director : public Supervisor
{
public:
    Director(QString, QString, Position, AttendanceLog*, LeaveBalance*, bool);
    virtual ~Director();

    QVector<PendingList>_getPendingList();

    virtual void _approveOrRejectLeave(QString AID, bool isApprove) override;
    void addtofile(const LeaveRecord& record, bool isApproved);

    bool isDirector()
    {
        return true;
    }




private:
    AttendanceLog* log;
    QVector<PendingList> pendingList;
};

#endif
