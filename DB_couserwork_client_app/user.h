#ifndef USER_H
#define USER_H
#include <QString>

/*
 * Это класс для авторизации.
 * С помощью него будет передаваться информация об
 * прошедшем авторизацию пользователе.
 */

class User
{
public:
    User(int _id, QString _login);
    int getId();
    QString getLogin();

private:
    int id;
    QString login;
};

#endif // USER_H
