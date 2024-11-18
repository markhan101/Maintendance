#include "employee.h"

Employee::Employee(QString id, QString name, Position position, AttendanceLog* attlog, LeaveBalance leaveb):User(id,name), pos(position), attLog(attlog),leaveBalance(leaveb) {}

Employee::~Employee()
{
    delete attLog;
    attLog = nullptr;
}

void Employee::_login()
{
    //nothing yet
}

void Employee::_logout()
{
    //same here
}

void Employee::_storeInfo()
{
    //add to file text
}

void Employee::_applyForLeave(LeaveApplication *application) {
    // Logic for applying for leave
}
//std::vector<QString> Employee::_viewAttendance(QString uID) {
    // Logic for viewing attendance
//}


AttendanceLog* Employee::_viewAttendance( ) {
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
        return attLog;
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
            bool isPresent = (parts[2].trimmed() == "1");
            QString hoursStr = parts[3];

            int hours = hoursStr.toInt();
            qDebug() << hours;

            attLog->_addEntry(day, date, isPresent, hours);
        }
    }

    qDebug() << attLog;

    file.close();
    return attLog;
}

void Employee::_getAttendanceRecord() {
    // Logic for getting attendance record
}

void Employee::_getLeaveBalance() {
    // Logic for getting leave balance
}
