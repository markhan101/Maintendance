#ifndef LOGINPASS_H
#define LOGINPASS_H

#include <vector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "utils.h"

class Credential {
private:
    QString username;
    QString password;
    QString currentuser;
    Position position;
    
public:
    Credential(QString u, QString cu, QString p, Position pos);
    QString _getUsername() const;
    QString _getPassword() const;
    Position _getPosition() const;
    QString _getCurrentUser() const;
};

class LoginPass {
private:
    std::vector<Credential> credentials;
    void loadCredentials();

    Position determinePosition(const QString& username) const;

public:
    LoginPass();
    QString currentuser;
    bool validateCredentials(const QString& username, const QString& password, Position& pos) const;
};

#endif // LOGINPASS_H
