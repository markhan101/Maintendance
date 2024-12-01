#include "leavebalance.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

/**
 * @brief Constructor for LeaveBalance class.
 * Initializes the leave balance for the given user ID.
 * If the user ID is not empty, it loads the leave balance from the corresponding file.
 *
 * @param userId Unique identifier for the user (employee, director, etc.).
 */
LeaveBalance::LeaveBalance(const QString& userId) : userId(userId)
{
    if (!userId.isEmpty())
    {
        loadBalanceFromFile(); // Load the balance from the file if user ID is valid
    }
}

/**
 * @brief Loads the leave balance from the corresponding file.
 * Depending on the user ID prefix, it reads from a file located in the user's directory.
 */
void LeaveBalance::loadBalanceFromFile(){
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    // Determine the folder based on the user ID prefix
    QString folder;
    if (userId.startsWith('g')) {
        folder = "guard";
    } else if (userId.startsWith('d')) {
        folder = "director";
    } else if (userId.startsWith('e')) {
        folder = "emp";
    } else {
        folder = "supervisor";
        return; // Exit if no valid folder is found for the user
    }

    QString filePath = dir.absoluteFilePath(
        QString("records/%1/%2/%2_leavebalance.txt").arg(folder).arg(userId)
        );

    QFile file(filePath);
    qDebug() << "Attempting to load leave balance from file:" << filePath;

    // Attempt to open the leave balance file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not load leave balance file:" << filePath;
        return;
    }

    QTextStream in(&file);
    // Read the file line by line and extract leave balances
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;  // Skip empty lines

        QStringList parts = line.split('-');
        if (parts.size() >= 2) {
            QString type = parts[0].trimmed();
            int days = parts[1].trimmed().toInt();

            // Map the leave type to the corresponding balance entry
            if (type == "casual") balance[LeaveTypes::Casual] = days;
            else if (type == "earned") balance[LeaveTypes::Earned] = days;
            else if (type == "official") balance[LeaveTypes::Official] = days;
            else if (type == "unpaid") balance[LeaveTypes::Unpaid] = days;
            qDebug() << "Loaded leave balance:" << type << days;
        }
    }
    file.close();
}

/**
 * @brief Updates the leave balance for a specific leave type.
 * Reduces the balance for the specified leave type and saves the updated balance to the file.
 *
 * @param type The type of leave being updated (e.g., Casual, Earned).
 * @param days The number of days to subtract from the balance.
 * @param reason The reason for the leave (used in the balance file).
 */
void LeaveBalance::_updateLeaveBalance(LeaveTypes type, int days, QString reason)
{
    balance[type] -= days;  // Deduct the specified number of days from the balance
    saveBalanceToFile(reason); // Save the updated balance to the file
    qDebug() << "Updated leave balance for type" << type << "new balance:" << balance[type];
}

/**
 * @brief Retrieves the leave balance for a specific leave type.
 *
 * @param type The leave type (e.g., Casual, Earned).
 * @return int The current balance for the specified leave type.
 */
int LeaveBalance::_getLeaveBalance(LeaveTypes type)
{
    return balance[type];  // Return the balance for the given leave type
}

/**
 * @brief Placeholder for displaying the leave balance.
 * This function can be implemented to connect with the UI.
 */
void LeaveBalance::displayLeaveBalance()
{
    // To be implemented and connected with UI for displaying balance
}

/**
 * @brief Saves the current leave balance to the corresponding file.
 * This function writes the balance to the user's leave balance file.
 *
 * @param Reason The reason for saving the balance (used for auditing).
 * @return bool Returns true if the file was successfully saved, false otherwise.
 */
bool LeaveBalance::saveBalanceToFile(QString Reason) {
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");

    // Determine the folder based on the user ID prefix
    QString folder;
    if (userId.startsWith('g')) {
        folder = "guard";
    } else if (userId.startsWith('d')) {
        folder = "director";
    } else if (userId.startsWith('e')) {
        folder = "emp";
    } else {
        folder = "supervisor";
    }

    QString filePath = dir.absoluteFilePath(
        QString("records/%1/%2/%2_leavebalance.txt").arg(folder).arg(userId)
        );

    QFile file(filePath);
    // Attempt to open the file for writing
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open leave balance file for writing:" << filePath;
        return false;
    }

    QTextStream out(&file);
    // Write the current leave balances to the file
    out << "casual-" << balance[LeaveTypes::Casual] << "\n";
    out << "earned-" << balance[LeaveTypes::Earned] << "\n";
    out << "official-" << balance[LeaveTypes::Official] << "\n";
    out << "unpaid-" << balance[LeaveTypes::Unpaid] << "\n";

    file.close();
    return true;  // Return true if the file was saved successfully
}
