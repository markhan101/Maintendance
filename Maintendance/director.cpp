#include "director.h"


#include "leaveapplication.h"
#include "utils.h"

Director::Director(QString ID, QString name, Position pos, AttendanceLog* att_log, LeaveBalance* lb, bool dontReadPending)
    : Supervisor(ID, name, pos, att_log, lb, dontReadPending), log(nullptr)
{
    //read the pending list txt
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    QString sfilePath = dir.absoluteFilePath("records/director/d1/d1_pending.txt");
    QFile sFile(sfilePath);
    if (!sFile.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open Director pending file:" << sfilePath;
    }

    QTextStream in(&sFile);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(" - ");


        if (parts.size() == 2)
        {
            PendingList pending;
            pending.AID = parts[0].trimmed();
            pending.date = parts[1].trimmed();
            pendingList.push_back(pending);
        }
    }
    sFile.close();
}

Director::~Director()
{
    delete log;
    log = nullptr;
}

void Director::addtofile(const LeaveRecord& record, bool isApproved)
{
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    QString statusFileName = isApproved ? "approved.txt" : "rejected.txt";
    QString filePath = dir.absoluteFilePath(
        QString("records/director/d1/d1_%1").arg(statusFileName)
        );

    QFile file(filePath);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << record.ID << " - "
            << record.leaveType << " - "
            << record.fromDate << " - "
            << record.toDate << " - "
            << record.days << " - "
            << record.reason << " - "
            << QDate::currentDate().toString("yyyy-MM-dd") << "\n";
        file.close();
    }
}


QVector<PendingList> Director::_getPendingList()
{
    pendingList.clear(); // Clear existing data

    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    QString sPendingPath = dir.absoluteFilePath("records/director/d1/d1_pending.txt");
    QFile sFile(sPendingPath);

    if (sFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&sFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(" - ");

            if (parts.size() >= 2) {
                PendingList pending;
                pending.AID = parts[0].trimmed();
                pending.date = parts[1].trimmed();
                pendingList.push_back(pending);
            }
        }
        sFile.close();
    }

    return pendingList;

}

// Override _approveOrRejectLeave for Director
void Director::_approveOrRejectLeave(QString AID, bool isApprove)
{
    // Custom logic for Director's approval/rejection, if any
    // Or call Supervisor's version if Director shares the same logic
    Supervisor::_approveOrRejectLeave(AID, isApprove);
}



