#ifndef USER_H
#define USER_H
#include <string>
#include <QString>
class User
{
private:
    QString uID;
    QString uName;
public:

    User(QString, QString);
    virtual void _login() = 0;
    virtual void _logout() = 0;
    virtual void _storeInfo() = 0;
    void _set_uID(const QString ID);
    QString _get_uID();
    void _set_uName(const QString name);
    QString _get_uName() const;

};

#endif // USERLOGIN_H
