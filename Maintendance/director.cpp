#include "director.h"
#include "leaveapplication.h"
#include "utils.h"

Director::Director(QString ID, Position pos, AttendanceLog* att_log, LeaveBalance* lb)
    : Employee(ID, pos, att_log, lb), log(nullptr)
{
    //read the pending list txt
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    QString sfilePath = dir.absoluteFilePath("records/Director/d1/d1_pending.txt");
    QFile sFile(sfilePath);
    if (!sFile.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open Director pending file:" << sfilePath;
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

Director::~Director()
{
    delete log;
    log = nullptr;
}


QVector<PendingList> Director::_getPendingList()
{
    return this->pendingList;
}

void Director::_approveOrRejectLeave(QString AID, bool isApprove) {
    QString ID = AID.split('_').first();
    LeaveRecord record = _getRecord(AID);

    LeaveTypes type;

    if(record.leaveType == "3"){
            type = LeaveTypes::Unpaid;
    }


    LeaveBalance* balance = nullptr;
    LeaveApplication* leaveApp = nullptr;

    if (isApprove) {
        balance = new LeaveBalance(ID);
        leaveApp = new LeaveApplication(
            ID,
            AID,
            type,
            balance,
            record.fromDate,
            record.toDate,
            record.reason,
            QDate::currentDate().toString("yyyy-MM-dd"),
            "approved",
            record.days.toInt()
            );

        balance->_updateLeaveBalance(type, record.days.toInt(), record.reason);

    }

    addtofile(record, isApprove);


    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");


    QStringList pendingFiles = {
        "records/director/d1/d1_pending.txt"
    };

    for (const QString& pendingPath : pendingFiles) {
        QString filePath = dir.absoluteFilePath(pendingPath);
        QFile file(filePath);
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QString content = file.readAll();
            QStringList lines = content.split('\n');
            lines.removeIf([AID](const QString& line) {
                return line.startsWith(AID);
            });

            file.resize(0);
            QTextStream out(&file);
            out << lines.join('\n');
            file.close();
        }
    }


    QString folder = _getPreDir(ID);
    QString filePath = dir.absoluteFilePath(
        QString("records/%1/%2/%2_leaves.txt").arg(folder).arg(ID)
        );

    QFile file(filePath);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QString content = file.readAll();
        QStringList lines = content.split('\n');

        for (int i = 0; i < lines.size(); i++) {
            if (lines[i].startsWith(AID)) {
                QStringList parts = lines[i].split(" - ");
                if (parts.size() >= 7) {
                    parts[6] = isApprove ? "approved" : "rejected";
                    lines[i] = parts.join(" - ");
                }
                break;
            }
        }

        file.resize(0);
        QTextStream out(&file);
        out << lines.join('\n');
        file.close();
    }


    if (balance) delete balance;
    if (leaveApp) delete leaveApp;
}


void Director::addtofile(const LeaveRecord& record, bool isApproved) {
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
