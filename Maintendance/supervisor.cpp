#include "supervisor.h"
#include "leaveapplication.h"
#include "utils.h"

/**
 * Constructor for the Supervisor class.
 * It initializes the supervisor's ID, name, position, attendance log, and leave balance.
 * It also reads the supervisor's pending leave application list from a file.
 *
 * @param ID - Supervisor ID
 * @param name - Supervisor Name
 * @param pos - Supervisor Position (enum type)
 * @param att_log - Pointer to Attendance Log
 * @param lb - Pointer to Leave Balance
 */
Supervisor::Supervisor(QString ID, QString name, Position pos, AttendanceLog* att_log, LeaveBalance* lb)
    : Employee(ID, name, pos, att_log, lb), log(nullptr)
{
    // Read the pending list from a text file located in the supervisor's directory.
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../.."); // Navigate to root directory
    QString sfilePath = dir.absoluteFilePath("records/supervisor/s1/s1_pending.txt");
    QFile sFile(sfilePath);

    // Open the file for reading
    if (!sFile.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open supervisor pending file:" << sfilePath;
    }

    // Read and parse the file to load pending leave applications
    QTextStream in(&sFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" - ");

        // Ensure the format is valid before adding to the list
        if (parts.size() == 2) {
            PendingList pending;
            pending.AID = parts[0].trimmed(); // Application ID
            pending.date = parts[1].trimmed(); // Date
            pendingList.push_back(pending); // Add to the pending list
        }
    }
    sFile.close();
}

/**
 * Destructor for the Supervisor class.
 * Frees the dynamically allocated memory.
 */
Supervisor::~Supervisor()
{
    delete log;
    log = nullptr;
}

/**
 * Retrieves the pending leave application list for the supervisor.
 * This function clears the existing list and reloads it from the text file.
 *
 * @return QVector of PendingList containing the Application ID and the date.
 */
QVector<PendingList> Supervisor::_getPendingList()
{
    return this->pendingList;
}

/**
 * Approves or rejects a leave application.
 * Updates relevant files and modifies attendance logs if approved.
 *
 * @param AID - Application ID of the leave request.
 * @param isApprove - Boolean indicating whether the leave is approved (true) or rejected (false).
 */
void Supervisor::_approveOrRejectLeave(QString AID, bool isApprove)
{
    QString ID = AID.split('_').first(); // Extract employee ID from Application ID
    LeaveRecord record = _getRecord(AID); // Get the leave record details

    // Determine leave type based on the record
    LeaveTypes type;
    if (record.leaveType == "0") type = LeaveTypes::Casual;
    else if (record.leaveType == "1") type = LeaveTypes::Earned;
    else if (record.leaveType == "2") type = LeaveTypes::Official;
    else type = LeaveTypes::Unpaid;

    LeaveBalance* balance = nullptr;
    LeaveApplication* leaveApp = nullptr;

    if (isApprove) {
        // Create a new LeaveBalance and LeaveApplication if the leave is approved
        balance = new LeaveBalance(ID);
        leaveApp = new LeaveApplication(
            ID,
            AID,
            type,
            balance,
            record.fromDate,
            record.toDate,
            record.reason,
            QDate::currentDate().toString("yyyy-MM-dd"),
            "approved",
            record.days.toInt()
            );

        // Update leave balance and attendance logs
        balance->_updateLeaveBalance(type, record.days.toInt(), record.reason);
        QDate fromDate = QDate::fromString(record.fromDate, "yyyy/MM/dd");
        QDate toDate = QDate::fromString(record.toDate, "yyyy/MM/dd");
        _updateAttendanceForLeave(ID, type, fromDate, toDate);
    }

    addtofile(record, isApprove); // Add the record to the corresponding file (approved/rejected)

    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    // Determine which files to update based on leave type (unpaid or others)
    QStringList pendingFiles;
    if (type == LeaveTypes::Unpaid) {
        pendingFiles = {"records/supervisor/s1/s1_pending.txt"};
    } else {
        pendingFiles = {
            "records/supervisor/s1/s1_pending.txt",
            "records/director/d1/d1_pending.txt"
        };
    }

    // Remove the application from the pending files
    for (const QString& pendingPath : pendingFiles) {
        QString filePath = dir.absoluteFilePath(pendingPath);
        QFile file(filePath);
        if (file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QString content = file.readAll();
            QStringList lines = content.split('\n');
            lines.removeIf([AID](const QString& line) {
                return line.startsWith(AID); // Remove the line with matching Application ID
            });

            file.resize(0); // Clear file contents
            QTextStream out(&file);
            out << lines.join('\n'); // Write the updated content back to the file
            file.close();
        }
    }

    // Update the leave status in the employee's leave records
    QString folder = _getPreDir(ID);
    QString filePath = dir.absoluteFilePath(
        QString("records/%1/%2/%2_leaves.txt").arg(folder).arg(ID)
        );

    QFile file(filePath);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString content = file.readAll();
        QStringList lines = content.split('\n');

        // Modify the leave status (approved/rejected) for the specific leave record
        for (int i = 0; i < lines.size(); i++)
        {
            if (lines[i].startsWith(AID)) {
                QStringList parts = lines[i].split(" - ");
                if (parts.size() >= 7) {
                    if (type == LeaveTypes::Unpaid)
                    {
                        parts[6] = "pending";
                    } else {
                        parts[6] = isApprove ? "approved" : "rejected";
                    }
                    lines[i] = parts.join(" - ");
                }
                break;
            }
        }

        file.resize(0); // Clear file contents
        QTextStream out(&file);
        out << lines.join('\n'); // Write the updated content back to the file
        file.close();
    }

    // Clean up dynamically allocated memory
    if (balance) delete balance;
    if (leaveApp) delete leaveApp;
}

/**
 * Updates the attendance log for an employee based on the leave type and date range.
 *
 * @param ID - Employee ID
 * @param type - Type of leave (Casual, Earned, Official, Unpaid)
 * @param fromDate - Starting date of the leave
 * @param toDate - Ending date of the leave
 */
void Supervisor::_updateAttendanceForLeave(const QString& ID, LeaveTypes type, const QDate& fromDate, const QDate& toDate)
{
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../.."); // Navigate to root directory

    QString folder = _getPreDir(ID);
    QString filePath = dir.absoluteFilePath(
        QString("records/%1/%2/%2_attendancelogs.txt").arg(folder).arg(ID)
        );

    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Could not open attendance log file:" << filePath;
        return;
    }

    QTextStream out(&file);
    QDate currentDate = fromDate;

    // Update attendance logs for each day of the leave
    while (currentDate <= toDate)
    {
        QString dayStr = _getDayStr(currentDate.dayOfWeek());
        QString dateStr = currentDate.toString("yyyy/MM/dd");

        switch(type)
        {
            case LeaveTypes::Casual:
            // Casual leave: present but no hours logged
            out << dayStr << " - " << dateStr << " - " << "1" << " - " << "0" << "\n";
            break;

            case LeaveTypes::Earned:
            case LeaveTypes::Official:
            // Earned/Official leave: present with full 8 hours logged
            out << dayStr << " - " << dateStr << " - " << "1" << " - " << "8" << "\n";
            break;

            case LeaveTypes::Unpaid:
            // Unpaid leave: marked as UL with no hours logged
            out << dayStr << " - " << dateStr << " - " << "UL" << " - " << "0" << "\n";
            break;
        }

        currentDate = currentDate.addDays(1); // Move to the next day
    }

    file.close();
}

/**
 * Adds the leave record to either the approved or rejected file based on the status of the supervisor.
 *
 * @param record - LeaveRecord object containing the leave details.
 * @param isApproved - Boolean indicating whether the leave is approved (true) or rejected (false).
 */
void Supervisor::addtofile(const LeaveRecord& record, bool isApproved)
{
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    // Determine the target file (approved or rejected)
    QString statusFileName = isApproved ? "approved.txt" : "rejected.txt";
    QString filePath = dir.absoluteFilePath(
        QString("records/supervisor/s1/s1_%1").arg(statusFileName)
        );

    QFile file(filePath);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);

        // Write the leave record details to the file
        out << record.ID << " - "
            << record.leaveType << " - "
            << record.fromDate << " - "
            << record.toDate << " - "
            << record.days << " - "
            << record.reason << " - "
            << QDate::currentDate().toString("yyyy-MM-dd") << "\n";

        file.close();
    }
}
