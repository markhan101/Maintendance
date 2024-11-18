#include "leavebalance.h"

LeaveBalance::LeaveBalance(const LoginPass* lp) : loginPass(lp)
{
    

    if (loginPass){
        QString currentUser = loginPass->getCurrentUser();
        if (!currentUser.isEmpty()){
            loadBalanceFromFile();
        }
    }
}

void LeaveBalance::loadBalanceFromFile(){
    QString userId = loginPass->getCurrentUser();
    QString baseDir = QCoreApplication::applicationDirPath();
    QDir dir(baseDir);
    dir.cd("../../..");
    QString filePath = dir.absoluteFilePath(
        QString("records/emp/%1/%1_leavebalance.txt").arg(userId)
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
        }
    }
    file.close();


}

void LeaveBalance::_updateLeaveBalance(LeaveTypes type, int days)
{
    balance[type] -= days;
}

int LeaveBalance::_getLeaveBalance(LeaveTypes type)
{
    return balance[type];
}

void LeaveBalance::displayLeaveBalance()
{
    //to be implemented and connected with UI
}
