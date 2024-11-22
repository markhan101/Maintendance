#include "leaveapplication.h"

LeaveApplication::LeaveApplication(QString ID, LeaveTypes type, LeaveBalance* balance,QString fromDate,QString toDate, QString reason,QString genDate, QString status, int days):
    ID(ID), leaveType(type), balance(balance), fromDate(fromDate), toDate(toDate), reason(reason), applicationGeneratedDate(genDate), status(status),days(days){}


LeaveApplication::~LeaveApplication()
{

}


bool LeaveApplication::apply()
{
    return true;
}


void LeaveApplication::approve(QString id)
{

}

void LeaveApplication::reject(QString id)
{

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
        balance->_updateLeaveBalance(type, daysRequested, reason);

        // Save application to file
        QString baseDir = QCoreApplication::applicationDirPath();
        QDir dir(baseDir);
        dir.cd("../../..");
        QString Folder;
        
        if(ID[0]=='g'){
            Folder="guard";
        }
        else if (ID[0] == 'e'){
            Folder = "emp";
        }
        else if (ID[0]=='d'){
            Folder = "director";
        }
        else {
            Folder = "supervisor";
        }
        
        QString filePath = dir.absoluteFilePath(
            QString("records/%1/%2/%2_leave.txt").arg(Folder).arg(ID)
        );

        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return false;
        }

        QTextStream out(&file);
        out << "ID:" << ID << " - ";
        out << "Type:" << static_cast<int>(type) << " - "; 
        out << "From:" << fromDate << " - ";
        out << "To:" << toDate << " - ";
        out << "Days:" << daysRequested << " - ";
        out << "Reason:" << reason << " - ";
        out << "Status:" << status << "\n";
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

        // Save application to file
        QString baseDir = QCoreApplication::applicationDirPath();
        QDir dir(baseDir);
        dir.cd("../../..");
        QString Folder;
        //ID starts with g folder is guard
        if(ID[0]=='g'){
            Folder="guard";
        }
        else if (ID[0] == 'e'){
            Folder = "emp";
        }
        else if (ID[0]=='d'){
            Folder = "director";
        }
        else {
            Folder = "supervisor";
        }
        
        QString filePath = dir.absoluteFilePath(
            QString("records/%1/%2/%2_leave.txt").arg(Folder).arg(ID)
        );

        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
              
            return false;
        }

        QTextStream out(&file);
        out << "ID:" << ID << " - ";
        out << "Type:Casual - ";
        out << "From:" << fromDate << " - ";
        out << "To:" << toDate << " - ";
        out << "Days:" << days << " - ";
        out << "Reason:" << reason << " - ";
        out << "Status:" << status << "\n";
        file.close();

        return true;
    }
    return false;
}

