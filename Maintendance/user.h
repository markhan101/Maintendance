#ifndef USER_H
#define USER_H
#include <QString>
class User
{
private:
    QString uID;

public:

    User(QString);

    void _set_uID(const QString ID);
    QString _get_uID();
};

#endif // USERLOGIN_H
