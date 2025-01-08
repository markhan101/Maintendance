#include "director.h"
#include "leaveapplication.h"
#include "utils.h"

/**
 * @brief Constructor for Director class.
 * Initializes a Director instance and loads the pending leave applications from the pending file.
 *
 * @param ID Unique identifier for the Director.
 * @param pos Position of the Director.
 * @param att_log Pointer to the attendance log of the Director.
 * @param lb Pointer to the leave balance of the Director.
 */
Director::Director(QString ID, Position pos, AttendanceLog* att_log, LeaveBalance* lb)
    : Employee(ID, pos, att_log, lb), log(nullptr)
{
    // Read the pending list from the director's pending leave file
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    QString sfilePath = dir.absoluteFilePath("records/Director/d1/d1_pending.txt");
    QFile sFile(sfilePath);

    // Open the pending leave file for reading
    if (!sFile.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open Director pending file:" << sfilePath;
    }

    QTextStream in(&sFile);
    // Read each line and extract pending leave details
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" - ");

        if (parts.size() == 2) {
            PendingList pending;
            pending.AID = parts[0].trimmed();
            pending.date = parts[1].trimmed();
            pendingList.push_back(pending);
        }
    }
    sFile.close();
}

/**
 * @brief Destructor for Director class.
 * Cleans up any resources used by the Director.
 */
Director::~Director()
{
    delete log;
    log = nullptr;
}

/**
 * @brief Retrieves the list of pending leave applications for the Director.
 *
 * @return QVector<PendingList> A list of pending leave applications.
 */
QVector<PendingList> Director::_getPendingList()
{
    return this->pendingList;
}

/**
 * @brief Approves or rejects a leave application.
 * Updates the leave status and the leave balance accordingly.
 *
 * @param AID The employee's leave application ID.
 * @param isApprove Boolean indicating whether the leave is approved (true) or rejected (false).
 */
void Director::_approveOrRejectLeave(QString AID, bool isApprove) {
    QString ID = AID.split('_').first();  // Extract employee ID
    LeaveRecord record = _getRecord(AID); // Get the leave record associated with the AID

    LeaveTypes type;

    if(record.leaveType == "3"){
        type = LeaveTypes::Unpaid; // If leave type is "3", set it to Unpaid leave
    }

    LeaveBalance* balance = nullptr;
    LeaveApplication* leaveApp = nullptr;

    // If leave is approved, update leave balance and create leave application
    if (isApprove) {
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

        balance->_updateLeaveBalance(type, record.days.toInt()); // Update the leave balance
    }

    addtofile(record, isApprove); // Record the leave status in the appropriate file

    // Read the pending leave files and update them by removing the processed AID
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    QStringList pendingFiles = {
        "records/director/d1/d1_pending.txt"
    };

    // Iterate through all pending files and remove the processed leave application
    for (const QString& pendingPath : pendingFiles) {
        QString filePath = dir.absoluteFilePath(pendingPath);
        QFile file(filePath);
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QString content = file.readAll();
            QStringList lines = content.split('\n');
            lines.removeIf([AID](const QString& line) {
                return line.startsWith(AID); // Remove the line with the matching AID
            });

            file.resize(0);
            QTextStream out(&file);
            out << lines.join('\n'); // Write the updated content back to the file
            file.close();
        }
    }

    // Update the employee's leave file with the new leave status (approved/rejected)
    QString folder = _getPreDir(ID);  // Get the directory for the employee
    QString filePath = dir.absoluteFilePath(
        QString("records/%1/%2/%2_leaves.txt").arg(folder).arg(ID)
        );

    QFile file(filePath);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QString content = file.readAll();
        QStringList lines = content.split('\n');

        // Find and update the line for the corresponding leave application
        for (int i = 0; i < lines.size(); i++) {
            if (lines[i].startsWith(AID)) {
                QStringList parts = lines[i].split(" - ");
                if (parts.size() >= 7) {
                    parts[6] = isApprove ? "approved" : "rejected";  // Update status to approved or rejected
                    lines[i] = parts.join(" - ");
                }
                break;
            }
        }

        file.resize(0);
        QTextStream out(&file);
        out << lines.join('\n'); // Write the updated content back to the file
        file.close();
    }

    // Clean up dynamically allocated memory for balance and leave application
    if (balance) delete balance;
    if (leaveApp) delete leaveApp;
}

/**
 * @brief Adds the leave record to the director's approved or rejected leave file.
 *
 * @param record The leave record to be added.
 * @param isApproved Boolean indicating whether the leave is approved (true) or rejected (false).
 */
void Director::addtofile(const LeaveRecord& record, bool isApproved) {
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    QString statusFileName = isApproved ? "approved.txt" : "rejected.txt";  // Set file name based on status
    QString filePath = dir.absoluteFilePath(
        QString("records/director/d1/d1_%1").arg(statusFileName)
        );

    QFile file(filePath);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << record.ID << " - "
            << record.leaveType << " - "
            << record.fromDate << " - "
            << record.toDate << " - "
            << record.days << " - "
            << record.reason << " - "
            << QDate::currentDate().toString("yyyy-MM-dd") << "\n";  // Add record to file
        file.close();
    }
}
