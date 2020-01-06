#ifndef DATABASE_H
#define DATABASE_H
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QCryptographicHash>

class Database
{
public:
    Database();
    bool openDatabase();
    bool queryRegistration(const QString &login, const QString &pass, int access_level);
    int queryAuthorization(const QString &login, const QString &pass);
};

#endif // DATABASE_H
