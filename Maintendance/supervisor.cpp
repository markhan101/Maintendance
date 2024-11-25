#include "supervisor.h"
#include "leaveapplication.h"
#include "utils.h"

Supervisor::Supervisor(QString ID, QString name, Position pos, AttendanceLog* att_log, LeaveBalance* lb, bool readPending)
    : Employee(ID, name, pos, att_log, lb), log(nullptr)
{
    //read the pending list txt
    if(readPending)
    {
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


    LeaveBalance* balance = nullptr;
    LeaveApplication* leaveApp = nullptr;


    if(type == LeaveTypes::Unpaid )
    {
        if(this->isDirector())
        {
            //if this is director and he approves then update employee record his own pending
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
                //update employee balance file
                balance->_updateLeaveBalance(type, record.days.toInt(), record.reason);
            }

            //update app or rej of director file
            this->addtofile(record, isApprove);
            //remove from director pending
            //this->_removeFromPending();
            //update employee leaves.txt
            //leaveApplication->_updateEmpLeave(ID);
        }
        else
        {
            //just update supervisor
            this->addtofile(record, isApprove);
            //remove from director pending
            //this->_removeFromPending();

        }
    }
    else
    {
        //no need for director changes since director doesnt get any other type of leaves in his pending

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

            //update employee balance file
            balance->_updateLeaveBalance(type, record.days.toInt(), record.reason);
        }

        //update app or rej txt of supervisor
        addtofile(record,isApprove);
        //remove from supervisor pending
        //this->_removeFromPending();
        //update employee leaves.txt
        //leaveApplication->_updateEmpLeave(ID);

    }



    //!!!  REMOVE THESE LINES AND TURN THEM INTO THE ABOVE FUNCTIONS PLEASE




    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    QStringList pendingFiles;

    if (type == LeaveTypes::Unpaid){
     pendingFiles = {
        "records/supervisor/s1/s1_pending.txt",

        };
    }
    else{

        pendingFiles = {
        "records/supervisor/s1/s1_pending.txt",
        "records/director/d1/d1_pending.txt"
        };
    }


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
                if(type == LeaveTypes::Unpaid){
                        parts[6] = "pending";
                    }
                else{
                    parts[6] = isApprove ? "approved" : "rejected";
                        lines[i] = parts.join(" - ");}
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


void Supervisor::addtofile(const LeaveRecord& record, bool isApproved) {
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    
    QString statusFileName = isApproved ? "approved.txt" : "rejected.txt";
    QString filePath = dir.absoluteFilePath(
        QString("records/supervisor/s1/s1_%1").arg(statusFileName)
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
