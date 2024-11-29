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
