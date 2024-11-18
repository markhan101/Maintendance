#include "supervisor.h"

Supervisor::Supervisor(QString ID, QString name, Position pos, AttendanceLog* att_log, LeaveBalance* lb)
    : Employee(ID, name, pos, att_log, lb), log(nullptr)
{
}

Supervisor::~Supervisor()
{
    delete log;
    log = nullptr;
}
