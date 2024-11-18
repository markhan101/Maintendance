#ifndef USER_H
#define USER_H
#include <QString>
class User
{
private:
    QString uID;
    QString uName;
public:

    User(QString, QString);

    void _set_uID(const QString ID);
    QString _get_uID();
    void _set_uName(const QString name);
    QString _get_uName() const;

};

#endif // USERLOGIN_H
