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

    if (_isAttendanceMarked(id, entry->_getDate())) {
        return false; 
    }

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

bool Guard::_isAttendanceMarked(const QString& id, const QString& date) {
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    QString preDir = _getPreDir(id);
    QString filePath = dir.absoluteFilePath("records/" + preDir + "/" + id + "/" + id + "_attendancelogs.txt");
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    
    QDate targetDate = QDate::fromString(date, "yyyy/MM/dd");
    if (!targetDate.isValid()) {
        file.close();
        return false;
    }

    
    QStringList lines = QTextStream(&file).readAll().split('\n', Qt::SkipEmptyParts);
    file.close();

   
    for (int i = lines.size() - 1; i >= 0; --i) {
        QStringList parts = lines[i].split(" - ");
        if (parts.size() < 2) continue;

        QString existingDate = parts[1].trimmed();
        QDate entryDate = QDate::fromString(existingDate, "yyyy/MM/dd");
        
        
        if (entryDate < targetDate) {
            break;
        }

        // Check for match
        if (entryDate == targetDate) {
            QString status = parts[2].trimmed();
            QString statusMsg = status == "1" ? "present" : 
                              status == "0" ? "absent" : status;

            QMessageBox::warning(nullptr, "Duplicate Entry", 
                QString("Attendance already marked as %1 for date %2")
                .arg(statusMsg)
                .arg(existingDate));
            return true;
        }
    }

    return false;
}


