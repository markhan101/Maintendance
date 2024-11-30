#include "employee.h"

Employee::Employee(QString id, Position position, AttendanceLog* attlog, LeaveBalance* leaveb)
    : User(id), pos(position), attLog(attlog), leaveBalance(leaveb)
{
    attLog = new AttendanceLog();
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    QString preDir = _getPreDir(this->_get_uID());
    //qDebug() << "The ID is: " << this->_get_uID();
    // qDebug() << "The predir is: " << preDir;



    QString filePath = dir.absoluteFilePath("records/" + preDir + "/" + this->_get_uID() + "/" + this->_get_uID() + "_attendancelogs.txt");

    qDebug() << "The ID is: " << this->_get_uID();
    qDebug() << "The filepath is: " << filePath;


    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "ERRORRRRR.";
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(" - ");

        if (parts.size() >= 4)
        {
            QString day = parts[0];
            QString date = parts[1];
            QString isPresent = (parts[2]);
            QString hoursStr = parts[3];

            int hours = hoursStr.toInt();
            qDebug() << hours;

            attLog->_addEntry(day, date, isPresent, hours);
        }
    }

    qDebug() << attLog;

    if(attLog->_getSize() == 0)
    {
        attLog = {};
    }

    file.close();
}



Employee::~Employee()
{
    delete attLog;
    delete leaveBalance;
}


QVector<LeaveRecord> Employee::getPendingApplications() {
    QVector<LeaveRecord> pendingLeaves;
    
    
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    
    
    QString folder = _getPreDir(_get_uID());
    QString filePath = dir.absoluteFilePath(
        QString("records/%1/%2/%2_leaves.txt").arg(folder).arg(_get_uID())
    );

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open leave file:" << filePath;
        return pendingLeaves;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" - ");
        
       
        if (parts.size() >= 7 && parts[6].trimmed() == "pending") {
            LeaveRecord record;
            record.ID = parts[0];  
            
            
            switch(parts[1].toInt()) {
                case 0: record.leaveType = "Casual"; break;
                case 1: record.leaveType = "Earned"; break;
                case 2: record.leaveType = "Official"; break;
                case 3: record.leaveType = "Unpaid"; break;
                default: record.leaveType = "Unknown";
            }
            
            record.fromDate = parts[2];
            record.toDate = parts[3];
            record.days = parts[4];
            record.reason = parts[5];
            record.status = parts[6];
            
            pendingLeaves.append(record);
        }
    }
    
    file.close();
    return pendingLeaves;
}






void Employee::_applyForLeave()
{
    // Logic for applying for leave
}
//std::vector<QString> Employee::_viewAttendance(QString uID) {
    // Logic for viewing attendance
//}


AttendanceLog* Employee::_viewAttendance()
{

    return attLog;
}

void Employee::_getAttendanceRecord() {
    // Logic for getting attendance record
}

void Employee::_getLeaveBalance() {
    // Logic for getting leave balance
}


QVector<LeaveBalanceRecord> Employee::getLeaveBalances() const {
    QVector<LeaveBalanceRecord> balances;
    
    if (!leaveBalance) return balances;
    

    LeaveBalanceRecord casualRecord;
    casualRecord.leaveType = "Casual";
    casualRecord.balance = leaveBalance->_getLeaveBalance(LeaveTypes::Casual);
    casualRecord.employeeId = _get_uID();
    balances.append(casualRecord);
    
    LeaveBalanceRecord earnedRecord;
    earnedRecord.leaveType = "Earned";
    earnedRecord.balance = leaveBalance->_getLeaveBalance(LeaveTypes::Earned);
    earnedRecord.employeeId = _get_uID();
    balances.append(earnedRecord);
    
    LeaveBalanceRecord officialRecord;
    officialRecord.leaveType = "Official";
    officialRecord.balance = leaveBalance->_getLeaveBalance(LeaveTypes::Official);
    officialRecord.employeeId = _get_uID();
    balances.append(officialRecord);
    
    LeaveBalanceRecord unpaidRecord;
    unpaidRecord.leaveType = "Unpaid";
    unpaidRecord.balance = leaveBalance->_getLeaveBalance(LeaveTypes::Unpaid);
    unpaidRecord.employeeId = _get_uID();
    balances.append(unpaidRecord);
    
    return balances;
}