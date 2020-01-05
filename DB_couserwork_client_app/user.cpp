#include "user.h"

User::User(int _id, QString _login)
{
    id = _id;
    login = _login;
}


int User::getId()
{
    return id;
}


QString User::getLogin()
{
    return login;
}
