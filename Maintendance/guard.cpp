#include "guard.h"

Guard::Guard(QString ID, QString name, Position pos, AttendanceLog *att_log, LeaveBalance lb) : Employee(ID, name, pos, att_log, lb), log(nullptr)
{
}

Guard::~Guard()
{
    delete log;
    log = nullptr;
}

bool Guard::_markAttendance(QString id, AttendanceEntry* entry)
{
    // Construct the file path
    // reminder to create a fileSystem class to handle all these tasks

    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    QString preDir = _getPreDir(id);
    QString filePath = dir.absoluteFilePath("records/" + preDir + "/" + id + "/" + id + "_attendancelogs.txt");
    QFile file(filePath);



    if(file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << entry->_getDay() << " - " << entry->_getDate() << " - " << entry->_isPresent() << " - " << entry->_getHours() << "\n";
        return true;
    }
    return false;
}


//redundancy needs to be fixed later....
// return this->_getAttendanceRecord();
AttendanceLog* Guard::_viewAttendance()
{
    // use the attendance balance to populate ui
    log = new AttendanceLog();
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
        return log;
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

            log->_addEntry(day, date, isPresent, hours);
        }
    }

    qDebug() << log;

    file.close();
    return log;

    // in actual we will return something like

    // and for that we will have to change the return type or write multiple functions


}
