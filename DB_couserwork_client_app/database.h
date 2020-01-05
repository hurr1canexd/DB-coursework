#ifndef DATABASE_H
#define DATABASE_H
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

class Database
{
public:
    Database();
    bool openDatabase();
};

#endif // DATABASE_H
