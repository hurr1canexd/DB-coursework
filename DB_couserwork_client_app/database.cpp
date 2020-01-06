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
    if (!db.open()) {
        qDebug() << "ERROR: " << QSqlError(db.lastError()).text();
        err = true;
    } else {
        qDebug() << "Произошло подключение к БД";
    }

    return err;
}

bool Database::queryRegistration(const QString &login, const QString &pass, int access_level)
{
    QString encoded_pass = QString(QCryptographicHash::hash(pass.toLocal8Bit(), QCryptographicHash::Md5).toHex());

    try {
        QSqlQuery query;
        query.prepare("EXEC dbo.Registration ?, ?, ?");
        query.bindValue(0, login);
        query.bindValue(1, encoded_pass);
        query.bindValue(2, access_level);
        query.exec();
        query.next();

        return query.value(0) == 1;
    } catch (...) {
        qDebug() << "Error in queryRegistration";
        return false;
    }
}

int Database::queryAuthorization(const QString &login, const QString &pass)
{
    QString encoded_pass = QString(QCryptographicHash::hash(pass.toLocal8Bit(), QCryptographicHash::Md5).toHex());

    try {
        QSqlQuery query;
        query.prepare("EXEC dbo.Authorize ?, ?");
        query.bindValue(0, login);
        query.bindValue(1, encoded_pass);
        query.exec();
        query.next();

        qDebug() << query.value(0) << query.value(0).toInt();
        return query.value(0).toInt();
    } catch (...) {
        qDebug() << "Error in queryAuthorization";
        return false;
    }
}
