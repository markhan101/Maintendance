#include "leaveapplication.h"

/**
 * @brief Constructor for LeaveApplication class.
 * Initializes a LeaveApplication instance with provided details.
 *
 * @param ID Unique identifier for the leave application.
 * @param aid Employee ID of the applicant.
 * @param type Type of leave (Casual, Earned, etc.).
 * @param balance Pointer to the LeaveBalance object representing the applicant's leave balance.
 * @param fromDate Start date of the leave.
 * @param toDate End date of the leave.
 * @param reason Reason for the leave.
 * @param genDate Date the leave application was generated.
 * @param status Current status of the leave application (e.g., Pending, Approved, Rejected).
 * @param days Number of days requested for the leave.
 */
LeaveApplication::LeaveApplication(QString ID, QString aid, LeaveTypes type, LeaveBalance* balance, QString fromDate, QString toDate, QString reason, QString genDate, QString status, int days):
    ID(ID), AID(aid), leaveType(type), balance(balance), fromDate(fromDate), toDate(toDate), reason(reason), applicationGeneratedDate(genDate), status(status), days(days) {}

/**
 * @brief Destructor for LeaveApplication class.
 * Cleans up the LeaveApplication object.
 */
LeaveApplication::~LeaveApplication() {}

/**
 * @brief Applies for a leave by adding the leave application to supervisor and director pending files.
 *
 * @return bool True if the leave application is successfully written to files, false otherwise.
 */
bool LeaveApplication::apply()
{
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    // Director file handling
    QString dfilePath = dir.absoluteFilePath("records/director/d1/d1_pending.txt");
    QFile dFile(dfilePath);
    if (!dFile.open(QIODevice::Append | QIODevice::Text))
    {
        qWarning() << "Failed to open director pending file:" << dfilePath;
        return false;
    }
    QTextStream dOut(&dFile);
    dOut << AID << " - " << QDate::currentDate().toString("yyyy-MM-dd") << "\n";
    dFile.close();

    // Supervisor file handling
    QString sfilePath = dir.absoluteFilePath("records/supervisor/s1/s1_pending.txt");
    QFile sFile(sfilePath);
    if (!sFile.open(QIODevice::Append | QIODevice::Text))
    {
        qWarning() << "Failed to open supervisor pending file:" << sfilePath;
        return false;
    }
    QTextStream sOut(&sFile);
    sOut << AID << " - " << QDate::currentDate().toString("yyyy-MM-dd") << "\n";
    sFile.close();

    return true;
}

/**
 * @brief Reads the approved leave applications from the employee's leave file.
 *
 * @param id Employee ID for which the approved leaves are to be fetched.
 * @return QVector<LeaveRecord>* A vector of LeaveRecord objects representing the approved leave applications.
 */
QVector<LeaveRecord>* LeaveApplication::_readApprovedApplication(QString id) {
    QVector<LeaveRecord>* approvedLeaves = new QVector<LeaveRecord>();

    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    QString Folder = FolderSelection(id);
    QString filePath = dir.absoluteFilePath(
        QString("records/%1/%2/%2_leaves.txt").arg(Folder).arg(id)
        );

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Could not open leave file:" << filePath;
        return approvedLeaves;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" - ");

        if (parts.size() >= 7 && parts[6].trimmed() == "approved")
        {
            LeaveRecord record;
            record.ID = parts[0];

            // Map leave type based on integer value
            switch(parts[1].toInt()) {
            case 0: record.leaveType = "Casual"; break;
            case 1: record.leaveType = "Earned"; break;
            case 2: record.leaveType = "Official"; break;
            case 3: record.leaveType = "Unpaid"; break;
            default: record.leaveType = "Unknown";
            }

            record.fromDate = parts[2];
            record.toDate = parts[3];
            record.days = parts[4];
            record.reason = parts[5];
            record.status = parts[6];

            approvedLeaves->push_back(record);
        }
    }
    file.close();

    return approvedLeaves;
}

/**
 * @brief Reads the rejected leave applications from the employee's leave file.
 *
 * @param id Employee ID for which the rejected leaves are to be fetched.
 * @return QVector<LeaveRecord>* A vector of LeaveRecord objects representing the rejected leave applications.
 */
QVector<LeaveRecord>* LeaveApplication::_readRejectedApplication(QString id)
{
    QVector<LeaveRecord>* rejectedLeaves = new QVector<LeaveRecord>();

    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    QString Folder = FolderSelection(id);
    QString filePath = dir.absoluteFilePath(
        QString("records/%1/%2/%2_leaves.txt").arg(Folder).arg(id)
        );

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Could not open leave file:" << filePath;
        return rejectedLeaves;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" - ");

        if (parts.size() >= 7 && parts[6].trimmed() == "rejected")
        {
            LeaveRecord record;
            record.ID = parts[0];

            // Map leave type based on integer value
            switch(parts[1].toInt()) {
            case 0: record.leaveType = "Casual"; break;
            case 1: record.leaveType = "Earned"; break;
            case 2: record.leaveType = "Official"; break;
            case 3: record.leaveType = "Unpaid"; break;
            default: record.leaveType = "Unknown";
            }

            record.fromDate = parts[2];
            record.toDate = parts[3];
            record.days = parts[4];
            record.reason = parts[5];
            record.status = parts[6];

            rejectedLeaves->push_back(record);
        }
    }
    file.close();

    return rejectedLeaves;
}

/**
 * @brief Returns the current status of the leave application.
 *
 * @return QString The status of the leave application (e.g., Pending, Approved, Rejected).
 */
QString LeaveApplication::getStatus() const
{
    return this->status;
}

/**
 * @brief Handles leave types other than casual short leave by checking balance and applying leave.
 *
 * @param type The type of leave being requested.
 * @param daysRequested The number of days being requested for the leave.
 * @return bool True if the leave application is successful, false otherwise.
 */
bool LeaveApplication::handleOtherLeaveTypes(LeaveTypes type, int daysRequested)
{
    if (!balance)
    {
        return false;
    }

    // Check if leave balance is sufficient
    if (balance->_getLeaveBalance(type) >= daysRequested)
    {
        // Save application to file
        QString baseDir = QCoreApplication::applicationDirPath();
        QDir dir(baseDir);
        dir.cd("../../..");
        QString Folder = FolderSelection(ID);

        QString filePath = dir.absoluteFilePath(
            QString("records/%1/%2/%2_leaves.txt").arg(Folder).arg(ID)
            );

        QFile file(filePath);
        file.open(QIODevice::Append | QIODevice::Text);

        QTextStream out(&file);
        out << AID << " - ";
        out << static_cast<int>(type) << " - ";
        out << fromDate << " - ";
        out << toDate << " - ";
        out << daysRequested << " - ";
        out << reason << " - ";
        out << status << "\n";
        file.close();

        if (apply())
            return true;
    }

    return false;
}

/**
 * @brief Handles casual short leave application by checking balance and updating leave balance.
 *
 * @return bool True if the casual leave application is successful, false otherwise.
 */
bool LeaveApplication::handleCasualShortLeave()
{
    if (!balance)
    {
        return false;
    }

    // Check if casual leave balance is sufficient
    if (balance->_getLeaveBalance(LeaveTypes::Casual) >= days)
    {
        balance->_updateLeaveBalance(LeaveTypes::Casual, days);

        QString baseDir = QCoreApplication::applicationDirPath();
        QDir dir(baseDir);
        dir.cd("../../..");
        QString Folder = FolderSelection(ID);

        status = "approved";

        QString filePath = dir.absoluteFilePath(
            QString("records/%1/%2/%2_leaves.txt").arg(Folder).arg(ID)
            );

        QFile file(filePath);

        if (!file.open(QIODevice::Append | QIODevice::Text))
        {
            qDebug() << "ERROR: Cannot open leave file!";
        }

        QTextStream out(&file);
        out << AID << " - ";
        out << leaveType << " - ";
        out << fromDate << " - ";
        out << toDate << " - ";
        out << days << " - ";
        out << reason << " - ";
        out << status << "\n";
        file.close();

        return true;
    }
    return false;
}
