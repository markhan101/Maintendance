#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "employee.h"
#include "utils.h"

class Supervisor : public Employee
{
public:
    Supervisor(QString, Position, AttendanceLog*, LeaveBalance*);
    virtual ~Supervisor();

    virtual QVector<PendingList> _getPendingList();

   virtual void _approveOrRejectLeave(QString AID, bool isApprove);
    void _removePendingLeave(QString &AID)
    {
        for (int i = 0; i < pendingList.size(); ++i)
        {
            if (pendingList[i].AID == AID)
            {
                pendingList.remove(i);
                break;
            }
        }
    }
    void addtofile(const LeaveRecord& record, bool isApproved);
    void _updateAttendanceForLeave(const QString& ID, LeaveTypes type, const QDate& fromDate, const QDate& toDate);

   // QVector<QString> _fetchEIDs();






    virtual bool isDirector()
    {
        return false;
    }
    

private:
    AttendanceLog *log;
    QVector<PendingList> pendingList;
};

#endif // SUPERVISOR_H
