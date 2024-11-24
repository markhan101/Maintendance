#include "supervisor.h"

Supervisor::Supervisor(QString ID, QString name, Position pos, AttendanceLog* att_log, LeaveBalance* lb)
    : Employee(ID, name, pos, att_log, lb), log(nullptr)
{
    //read the pending list txt
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    QString sfilePath = dir.absoluteFilePath("records/supervisor/s1/s1_pending.txt");
    QFile sFile(sfilePath);
    if (!sFile.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open supervisor pending file:" << sfilePath;
    }

    QTextStream in(&sFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" - ");


        if (parts.size() == 2) {
            PendingList pending;
            pending.AID = parts[0].trimmed();
            pending.date = parts[1].trimmed();
            pendingList.push_back(pending);
        }
    }
    sFile.close();
}

Supervisor::~Supervisor()
{
    delete log;
    log = nullptr;
}


QVector<PendingList> Supervisor::_getPendingList()
{
    return pendingList;
}


void Supervisor::_approveOrRejectLeave(QString AID, bool isApprove)
{

    QString ID = AID.split('_').first();



}
