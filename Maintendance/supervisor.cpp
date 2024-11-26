#include "supervisor.h"
#include "leaveapplication.h"
#include "utils.h"

Supervisor::Supervisor(QString ID, QString name, Position pos, AttendanceLog *att_log, LeaveBalance *lb, bool readPending)
    : Employee(ID, name, pos, att_log, lb), log(nullptr)
{
    // read the pending list txt
    if (readPending)
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
}

Supervisor::~Supervisor()
{
    delete log;
    log = nullptr;
}

QVector<PendingList> Supervisor::_getPendingList()
{
    pendingList.clear(); // Clear existing data

    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    QString sPendingPath = dir.absoluteFilePath("records/supervisor/s1/s1_pending.txt");
    QFile sFile(sPendingPath);

    if (sFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&sFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList parts = line.split(" - ");

            if (parts.size() >= 2)
            {
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
    if (record.leaveType == "0")
        type = LeaveTypes::Casual;
    else if (record.leaveType == "1")
        type = LeaveTypes::Earned;
    else if (record.leaveType == "2")
        type = LeaveTypes::Official;
    else
        type = LeaveTypes::Unpaid;

    LeaveBalance* balance = nullptr;
    LeaveApplication* leaveApp = nullptr;

    if (type == LeaveTypes::Unpaid) {
        if (this->isDirector()) {
            if (isApprove) {
                balance = new LeaveBalance(ID);
                leaveApp = new LeaveApplication(
                    ID, AID, type, balance,
                    record.fromDate, record.toDate, record.reason,
                    QDate::currentDate().toString("yyyy-MM-dd"),
                    "approved", record.days.toInt()
                );
                balance->_updateLeaveBalance(type, record.days.toInt(), record.reason);
                
                // Update director's approval file
                addtofile(record, isApprove);
                
                // Remove from director's pending list
                _removePendingLeave(AID);
                
                // Update employee's leave status
                _updateEmployeeLeaveStatus(ID, AID, true);
            }
        } else {
            // For supervisor handling unpaid leave
            addtofile(record, isApprove);
            _removePendingLeave(AID);
        }
    } else {
        // For non-unpaid leaves (only supervisor handles these)
        if (isApprove) {
            balance = new LeaveBalance(ID);
            leaveApp = new LeaveApplication(
                ID, AID, type, balance,
                record.fromDate, record.toDate, record.reason,
                QDate::currentDate().toString("yyyy-MM-dd"),
                "approved", record.days.toInt()
            );

            // Update balance and attendance
            balance->_updateLeaveBalance(type, record.days.toInt(), record.reason);
            QDate fromDate = QDate::fromString(record.fromDate, "yyyy/MM/dd");
            QDate toDate = QDate::fromString(record.toDate, "yyyy/MM/dd");
            _updateAttendanceForLeave(ID, type, fromDate, toDate);
        }

        // Update supervisor's approval/rejection file
        addtofile(record, isApprove);
        
        // Remove from pending lists
        _removePendingLeave(AID);
        
        // Update employee's leave status
        _updateEmployeeLeaveStatus(ID, AID, isApprove);
    }

    // Clean up
    if (balance) delete balance;
    if (leaveApp) delete leaveApp;
}


void Supervisor::_updateEmployeeLeaveStatus(const QString& ID, const QString& AID, bool isApproved) {
    QString folder = _getPreDir(ID);
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    
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
                    parts[6] = isApproved ? "approved" : "rejected";
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
}

void Supervisor::_updateAttendanceForLeave(const QString &ID, LeaveTypes type, const QDate &fromDate, const QDate &toDate)
{
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    QString folder = _getPreDir(ID);
    QString filePath = dir.absoluteFilePath(
        QString("records/%1/%2/%2_attendancelogs.txt").arg(folder).arg(ID));

    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Could not open attendance log file:" << filePath;
        return;
    }

    QTextStream out(&file);
    QDate currentDate = fromDate;

    while (currentDate <= toDate)
    {
        QString dayStr = _getDayStr(currentDate.dayOfWeek());
        QString dateStr = currentDate.toString("yyyy/MM/dd");

        switch (type)
        {
        case LeaveTypes::Casual:
            // Present but no hours
            out << dayStr << " - " << dateStr << " - " << "1" << " - " << "0" << "\n";
            break;

        case LeaveTypes::Earned:
        case LeaveTypes::Official:
            // Present with 8 hours
            out << dayStr << " - " << dateStr << " - " << "1" << " - " << "8" << "\n";
            break;

        case LeaveTypes::Unpaid:
            // Marked as UL with no hours
            out << dayStr << " - " << dateStr << " - " << "UL" << " - " << "0" << "\n";
            break;
        }

        currentDate = currentDate.addDays(1);
    }

    file.close();
}

void Supervisor::addtofile(const LeaveRecord &record, bool isApproved)
{
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    QString statusFileName = isApproved ? "approved.txt" : "rejected.txt";
    QString filePath = dir.absoluteFilePath(
        QString("records/supervisor/s1/s1_%1").arg(statusFileName));

    QFile file(filePath);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
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
