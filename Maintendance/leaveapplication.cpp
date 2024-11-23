#include "leaveapplication.h"

LeaveApplication::LeaveApplication(QString ID, LeaveTypes type, LeaveBalance* balance,QString fromDate,QString toDate, QString reason,QString genDate, QString status, int days):
    ID(ID), leaveType(type), balance(balance), fromDate(fromDate), toDate(toDate), reason(reason), applicationGeneratedDate(genDate), status(status),days(days){}


LeaveApplication::~LeaveApplication()
{

}


bool LeaveApplication::apply()
{
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    // Director file handling
    QString dfilePath = dir.absoluteFilePath("records/director/d1/d1_pending.txt");
    QFile dFile(dfilePath);
    if (!dFile.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Failed to open director pending file:" << dfilePath;
        return false;
    }
    QTextStream dOut(&dFile);
    dOut << ID << " - " 
         << static_cast<int>(leaveType) << " - " 
         << fromDate << " - " 
         << toDate << " - " 
         << days << " - " 
         << reason << " - " 
         << status << "\n";
    dFile.close();

    // Supervisor file handling
    QString sfilePath = dir.absoluteFilePath("records/supervisor/s1/s1_pending.txt");
    QFile sFile(sfilePath);
    if (!sFile.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Failed to open supervisor pending file:" << sfilePath;
        return false;
    }
    QTextStream sOut(&sFile);
    sOut << ID << " - " 
         << static_cast<int>(leaveType) << " - " 
         << fromDate << " - " 
         << toDate << " - " 
         << days << " - " 
         << reason << " - " 
         << status << "\n";
    sFile.close();

    return true;
}

QString LeaveApplication::FolderSelection(QString id){
     QString Folder;
     if(id[0]=='g'){
            Folder="guard";
        }
        else if (id[0] == 'e'){
            Folder = "emp";
        }
        else if (id[0]=='d'){
            Folder = "director";
        }
        else {
            Folder = "supervisor";
        }
    return Folder;

}



QVector<LeaveRecord>* LeaveApplication::_readApprovedApplication(QString id) {
    QVector<LeaveRecord>* approvedLeaves = new QVector<LeaveRecord>();
    
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    
    QString Folder = FolderSelection(id);
    QString filePath = dir.absoluteFilePath(
        QString("records/%1/%2/%2_leave.txt").arg(Folder).arg(id)
    );

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open leave file:" << filePath;
        return approvedLeaves;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" - ");
        
       
        if (parts.size() >= 7 && parts[6].trimmed() == "approved") {
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
            
            approvedLeaves->push_back(record);
        }
    }
    file.close();
    
    return approvedLeaves;
}

QVector<LeaveRecord>* LeaveApplication::_readRejectedApplication(QString id) {
    QVector<LeaveRecord>* rejectedLeaves = new QVector<LeaveRecord>();
    
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    
    QString Folder = FolderSelection(id);
    QString filePath = dir.absoluteFilePath(
        QString("records/%1/%2/%2_leave.txt").arg(Folder).arg(id)
    );

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open leave file:" << filePath;
        return rejectedLeaves;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" - ");
        
       
        if (parts.size() >= 7 && parts[6].trimmed() == "rejected") {
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
            
            rejectedLeaves->push_back(record);
        }
    }
    file.close();
    
    return rejectedLeaves;
}






QString LeaveApplication::getStatus()const
{
    return this->status;
}

bool LeaveApplication::handleOtherLeaveTypes(LeaveTypes type, int daysRequested) {
    if (!balance) {
        return false;
    }

    if (balance->_getLeaveBalance(type) >= daysRequested) {
       

        // Save application to file
        QString baseDir = QCoreApplication::applicationDirPath();
        QDir dir(baseDir);
        dir.cd("../../..");
        QString Folder = FolderSelection(ID);
        
       
        
        QString filePath = dir.absoluteFilePath(
            QString("records/%1/%2/%2_leave.txt").arg(Folder).arg(ID)
        );

        if(apply()){
            qDebug() << "Application sent for approval";
        }

        QFile file(filePath);
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            return false;
        }

        QTextStream out(&file);
        out << ID << " - ";
        out << static_cast<int>(type) << " - "; 
        out << fromDate << " - ";
        out << toDate << " - ";
        out << daysRequested << " - ";
        out << reason << " - ";
        out << status << "\n";
        file.close();

        return true;
    }
    return false;
}



bool LeaveApplication::handleCasualShortLeave()
{
    if (!balance) {
     
        return false;
    }
   

    if (balance->_getLeaveBalance(LeaveTypes::Casual) >= days) {
        balance->_updateLeaveBalance(LeaveTypes::Casual, days, reason);

        
        QString baseDir = QCoreApplication::applicationDirPath();
        QDir dir(baseDir);
        dir.cd("../../..");
        QString Folder = FolderSelection(ID);
        //ID starts with g folder is guard
        

        
        status = "approved";
        
        QString filePath = dir.absoluteFilePath(
            QString("records/%1/%2/%2_leave.txt").arg(Folder).arg(ID)
        );

        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
              
            return false;
        }

        QTextStream out(&file);
        out << ID << " - ";
        out << leaveType << " - ";
        out << fromDate << " - ";
        out << toDate << " - ";
        out << days << " - ";
        out << reason << " - ";
        out << status << "\n";
        file.close();

        return true;
    }
    return false;
}

