#include "leavebalance.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

LeaveBalance::LeaveBalance(const QString& userId) : userId(userId)
{
    if (!userId.isEmpty())
    {
        loadBalanceFromFile();
    }
}

void LeaveBalance::loadBalanceFromFile(){
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    QString folder;
    if (userId.startsWith('g')) {
        folder = "guard";
    } else if (userId.startsWith('d')) {
        folder = "director";
    } else if (userId.startsWith('e')) {
        folder = "emp";
    } else {
       folder = "supervisor";
        return;
    }
    QString filePath = dir.absoluteFilePath(
        QString("records/%1/%2/%2_leavebalance.txt").arg(folder).arg(userId)
    );

    QFile file(filePath);
    qDebug() << "Attempting load leave balance txt" << filePath;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not load leave balance file:" << filePath;
        return;
    }

      QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split('-');
        if (parts.size() >= 2) {
            QString type = parts[0].trimmed();
            int days = parts[1].trimmed().toInt();

            if (type == "casual") balance[LeaveTypes::Casual] = days;
            else if (type == "earned") balance[LeaveTypes::Earned] = days;
            else if (type == "official") balance[LeaveTypes::Official] = days;
            else if (type == "unpaid") balance[LeaveTypes::Unpaid] = days;
            qDebug() << "Loaded leave balance:" << type << days;
        }
    }
    file.close();



}

void LeaveBalance::_updateLeaveBalance(LeaveTypes type, int days, QString reason)
{
    balance[type] -= days;
    saveBalanceToFile(reason);
}

int LeaveBalance::_getLeaveBalance(LeaveTypes type)
{
    return balance[type];
}

void LeaveBalance::displayLeaveBalance()
{
    //to be implemented and connected with UI

}


bool LeaveBalance::saveBalanceToFile(QString Reason) {
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    
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
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open leave balance file for writing:" << filePath;
        return false;
    }

    QTextStream out(&file);
    out << "casual-" << balance[LeaveTypes::Casual] << "\n";
    out << "earned-" << balance[LeaveTypes::Earned] << "\n";
    out << "official-" << balance[LeaveTypes::Official] << "\n";
    out << "unpaid-" << balance[LeaveTypes::Unpaid] << "\n";
   

    file.close();
    return true;
}
