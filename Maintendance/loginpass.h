#ifndef LOGINPASS_H
#define LOGINPASS_H

#include <vector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>
#include "utils.h"

class Credential {
private:
    QString username;
    QString password;
    Position position;
    
public:
    Credential(QString u,  QString p, Position pos);
    QString _getUsername() const;
    QString _getPassword() const;
    Position _getPosition() const;
   
};

class LoginPass {
private:
    std::vector<Credential> credentials;
    void loadCredentials();
    QString currentuser;
    Position determinePosition(const QString& username) const;

public:
    LoginPass();
    bool validateCredentials(const QString& username, const QString& password, Position& pos); // Remove const, change first param to const ref
    QString getCurrentUser() const { return currentuser; }
};

#endif // LOGINPASS_H
