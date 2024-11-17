#include "guard.h"



Guard::Guard(int ID, std::string name, Position pos, AttendanceLog att_log, LeaveBalance lb) : Employee(ID, name, pos, att_log, lb), log(nullptr)
{}

void Guard::_markAttendance(std::string id, bool ispresent, QDate date, int hours = 8)
{
    // Construct the file path
    QString baseDir = QCoreApplication::applicationDirPath();
    qDebug() << baseDir;
    QDir dir(baseDir);
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();

    //dir.cd();
    qDebug() << dir;

    /*QString filePath = QString("%1/%2.txt").arg(baseDir, QString::fromStdString(id));

    QFile file(filePath);

    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);

        QDateTime current = QDateTime::currentDateTime();
        QString dateStr = current.toString("d/M/yyyy");

        stream << dateStr << " - " << ispresent << " - " << hours << Qt::endl;

        qDebug() << "Attendance marked in: " << filePath.toStdString();
        file.close();
    }
    else
    {
        std::cerr << "Failed to open file for writing: " << filePath.toStdString() << std::endl;
    }
*/
}

AttendanceLog *Guard::_viewAttendance()
{
    // use the attendance balance to populate ui
    log = new AttendanceLog();
    QString baseDir = "E:/SDA/Maintendance/Maintendance";
    QString filePath = baseDir + "/emp6.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Could not open file: " << filePath.toStdString() << std::endl;
        return log;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(" - ");

        if (parts.size() >= 3)
        {

            QString date = parts[0];

            bool isPresent = (parts[1].trimmed() == "1");

            QString hoursStr = parts[2];
            int hours = hoursStr.toInt();
            qDebug() << hours;

            log->_addEntry(date.toStdString(), isPresent, hours);
        }
    }

    qDebug() << log;

    file.close();
    return log;

    // in actual we will return something like
    // return this->_getAttendanceRecord();
    // and for that we will have to change the return type or write multiple functions
}
