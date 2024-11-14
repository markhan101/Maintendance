#include "user.h"

User::User()
{

}
void User::_set_uID(const int ID)
{
    this->uID = ID;
}
int User::_get_uID() const
{
    return this->uID;
}
void User::_set_uName(const std::string name)
{
    this->uName = name;
}
std::string User::_get_uName() const
{
    return this->uName;
}
