#include "supervisor.h"
#include "leaveapplication.h"
#include "utils.h"

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


QVector<PendingList> Supervisor::_getPendingList() {
    pendingList.clear(); // Clear existing data

    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    QString sPendingPath = dir.absoluteFilePath("records/supervisor/s1/s1_pending.txt");
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

void Supervisor::_approveOrRejectLeave(QString AID, bool isApprove) {
    QString ID = AID.split('_').first();
    
    
    LeaveRecord record = _getRecord(AID);
    
    
    LeaveTypes type;
    if (record.leaveType == "0") type = LeaveTypes::Casual;
    else if (record.leaveType == "1") type = LeaveTypes::Earned;
    else if (record.leaveType == "2") type = LeaveTypes::Official;
    else type = LeaveTypes::Unpaid;
    
    LeaveBalance* balance = new LeaveBalance(ID);
    
    LeaveApplication* leaveApp = new LeaveApplication(
        ID,
        AID, 
        type,
        balance,
        record.fromDate,
        record.toDate,
        record.reason,
        QDate::currentDate().toString("yyyy-MM-dd"),
        isApprove ? "approved" : "rejected",
        record.days.toInt()
    );

    
    if (isApprove) {
        balance->_updateLeaveBalance(type, record.days.toInt(), record.reason);
    }

    
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    
   
    QStringList pendingFiles = {
        "records/supervisor/s1/s1_pending.txt",
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

    delete leaveApp;
    delete balance;
}
