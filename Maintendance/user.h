#ifndef USER_H
#define USER_H
#include <string>

class User
{
private:
    int uID;
    std::string uName;
public:
    User();
    virtual void _login() = 0;
    virtual void _logout() = 0;
    void _set_uID(const int ID);
    int _get_uID() const;
    void _set_uName(const std::string name);
    std::string _get_uName() const;

};

#endif // USERLOGIN_H
