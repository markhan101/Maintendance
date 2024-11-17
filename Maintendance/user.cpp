#include "user.h"

User::User(QString ID, QString name):uID(ID), uName(name){}

void User::_set_uID(const QString ID)
{
    this->uID = ID;
}
QString User::_get_uID()
{
    return this->uID;
}
void User::_set_uName(const QString name)
{
    this->uName = name;
}
QString User::_get_uName() const
{
    return this->uName;
}
