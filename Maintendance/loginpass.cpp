#include "loginpass.h"
#include <QDebug>

// Credential implementation
Credential::Credential(QString u, QString cu, QString p, Position pos)
    : username(u), password(p), position(pos) ,currentuser(cu) {}

QString Credential::_getUsername() const { 
    return username; 
}

QString Credential::_getPassword() const { 
    return password; 
}

Position Credential::_getPosition() const { 
    return position; 
}

// LoginPass implementation
LoginPass::LoginPass() {
    loadCredentials();
}

void LoginPass::loadCredentials() {
    QString baseDir = "E:/SDA/Maintendance/Maintendance";
    QString filePath = QString("%1/login.txt").arg(baseDir);

    //qDebug() << "Loading credentials from:" << filePath;
    
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Cannot open credentials file.";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split('-');
        if (parts.size() >= 2) {
            QString username = parts[0].trimmed();
            QString password = parts[1].trimmed();
            qDebug () << username << password;
            Position position = determinePosition(username);
            credentials.emplace_back(username, username, password, position);
        }
    }
    file.close();
}

Position LoginPass::determinePosition(const QString& username) const {
    if (username.startsWith("g")) return Position::guard;
    if (username.startsWith("e")) return Position::normal_employee;
    if (username.startsWith("s")) return Position::supervisor;
    if (username.startsWith("d")) return Position::director;
    return Position::guard;
}

bool LoginPass::validateCredentials(const QString& username, const QString& password, Position& pos) const {
    for (const auto& cred : credentials) {
        if (cred._getUsername() == username && cred._getPassword() == password) {
            pos = cred._getPosition();
           // currentuser = username;
            return true;
        }
    }
    return false;
}
