#include "guard.h"

// Constructor for Guard class
Guard::Guard(QString ID, Position pos, AttendanceLog* att_log, LeaveBalance* leaveBal)
    : Employee(ID, pos, att_log, leaveBal)  // Initialize the base class Employee
{
}

// Destructor for Guard class
Guard::~Guard()
{
    delete log;  // Delete the attendance log object (assumed to be a pointer)
    log = nullptr;  // Nullify the pointer after deletion
}

/**
 * @brief Marks the attendance for a guard.
 * This function appends attendance entry to the appropriate log file.
 *
 * @param id Employee ID.
 * @param entry AttendanceEntry object containing details like date, presence status, and hours worked.
 * @return true if attendance was marked successfully, false otherwise.
 */
bool Guard::_markAttendance(QString id, AttendanceEntry* entry)
{
    // Check if the attendance is already marked for the given date
    if (_isAttendanceMarked(id, entry->_getDate())) {
        return false;  // Do not mark attendance if it's already marked
    }

    // Construct the file path where attendance logs are stored
    QString baseDir = QCoreApplication::applicationDirPath();  // Get the application's base directory
    QDir dir(baseDir);
    dir.cd("../../..");  // Navigate to the parent directory

    QString preDir = _getPreDir(id);  // Get the specific directory for the user (e.g., guard directory)
    QString filePath = dir.absoluteFilePath("records/" + preDir + "/" + id + "/" + id + "_attendancelogs.txt");
    QFile file(filePath);  // Create a QFile object for the attendance log file

    qDebug() << filePath;  // Output file path to the debug console for inspection

    // Try to open the file in append mode to add a new attendance entry
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);  // Create a text stream for writing to the file
        stream << entry->_getDay() << " - " << entry->_getDate() << " - " << entry->_isPresent() << " - " << entry->_getHours() << "\n";
        return true;  // Successfully added the attendance entry
    }
    return false;  // Failed to open the file or append the data
}

/**
 * @brief Checks if attendance has already been marked for a specific date.
 *
 * @param id Employee ID.
 * @param date The date to check.
 * @return true if attendance has already been marked, false otherwise.
 */
bool Guard::_isAttendanceMarked(const QString& id, const QString& date)
{
    QString baseDir = QCoreApplication::applicationDirPath();  // Get the application's base directory
    QDir dir(baseDir);
    dir.cd("../../..");  // Navigate to the parent directory

    QString preDir = _getPreDir(id);  // Get the specific directory for the user
    QString filePath = dir.absoluteFilePath("records/" + preDir + "/" + id + "/" + id + "_attendancelogs.txt");
    QFile file(filePath);  // Create a QFile object for the attendance log file

    // Try to open the file in read-only mode
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;  // If the file can't be opened, assume no attendance is marked
    }

    QDate targetDate = QDate::fromString(date, "yyyy/MM/dd");  // Convert the input date to a QDate object
    if (!targetDate.isValid()) {
        file.close();  // Close the file if the date is invalid
        return false;  // Invalid date format
    }

    // Read all lines from the attendance file
    QStringList lines = QTextStream(&file).readAll().split('\n', Qt::SkipEmptyParts);
    file.close();  // Close the file after reading

    // Iterate through the lines in reverse order (most recent first)
    for (int i = lines.size() - 1; i >= 0; --i) {
        QStringList parts = lines[i].split(" - ");  // Split each line by " - " to extract the parts
        if (parts.size() < 2) continue;  // Skip invalid lines

        QString existingDate = parts[1].trimmed();  // Extract the date from the line
        QDate entryDate = QDate::fromString(existingDate, "yyyy/MM/dd");  // Convert the date to QDate object

        if (entryDate < targetDate) {
            break;  // If the existing entry's date is earlier, stop checking
        }

        // Check if the current entry's date matches the target date
        if (entryDate == targetDate) {
            QString status = parts[2].trimmed();  // Get the attendance status (present/absent)
            QString statusMsg = status == "1" ? "present" :
                                    status == "0" ? "absent" : status;

            // Show a warning message if the attendance has already been marked
            QMessageBox::warning(nullptr, "Duplicate Entry",
                                 QString("Attendance already marked as %1 for date %2")
                                     .arg(statusMsg)
                                     .arg(existingDate));
            return true;  // Attendance is already marked for the given date
        }
    }

    return false;  // No attendance found for the given date
}
