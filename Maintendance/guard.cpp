#include "guard.h"

Guard::Guard(QString ID, Position pos, AttendanceLog* att_log, LeaveBalance* leaveBal)
    : Employee(ID, pos, att_log, leaveBal)
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


    qDebug() << filePath;



    if(file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << entry->_getDay() << " - " << entry->_getDate() << " - " << entry->_isPresent() << " - " << entry->_getHours() << "\n";
        return true;
    }
    return false;
}


