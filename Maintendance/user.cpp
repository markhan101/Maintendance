#include "user.h"

User::User(QString ID):uID(ID){}
void User::_set_uID(const QString ID)
{
    this->uID = ID;
}
QString User::_get_uID()
{
    return this->uID;
}

