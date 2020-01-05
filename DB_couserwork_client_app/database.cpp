#include "database.h"

Database::Database()
{
}


bool Database::openDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server};SERVER=LAPTOP-62M928B6\\SQLEXPRESS;DATABASE=newDB;Trusted_Connection=yes;");
    db.setUserName("");
    db.setPassword("");

    bool err = false;
    if(!db.open()) {
        qDebug() << "ERROR: " << QSqlError(db.lastError()).text();
        err = true;
    } else {
        qDebug()<<"Ok";
    }

    return err;
}
