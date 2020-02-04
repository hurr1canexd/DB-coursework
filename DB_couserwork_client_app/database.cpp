#include "database.h"


bool Database::openDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server};SERVER=LAPTOP-62M928B6\\SQLEXPRESS;DATABASE=DBCookbook19;Trusted_Connection=yes;");
    db.setUserName("");
    db.setPassword("");

    bool err = false;
    if (!db.open()) {
//        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных");
        err = true;
        qDebug() << "ERROR: " << QSqlError(db.lastError()).text();
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

QString Database::queryGetLoginById(const int user_id)
{
    try {
        QSqlQuery query;
        query.prepare("EXEC dbo.GetLoginById ?");
        query.bindValue(0, user_id);
        query.exec();
        query.next();

        qDebug() << query.value(0);
        return query.value(0).toString();
    } catch (...) {
        qDebug() << "Error in queryGetLoginById";
        return "";
    }
}

int Database::queryAddRecipe(const QString &recipe_name, const QString &category, int calorie,
                             const QString &recipe_description, int cooking_time, int user_id)
{
    try {
        QSqlQuery query;
        query.prepare("EXEC dbo.AddRecipe ?, ?, ?, ?, ?, ?");
        query.bindValue(0, recipe_name);
        query.bindValue(1, category);
        query.bindValue(2, calorie);
        query.bindValue(3, recipe_description);
        query.bindValue(4, cooking_time);
        query.bindValue(5, user_id);
        query.exec();
        query.next();

        qDebug() << query.value(0) << query.value(0).toInt();
        return query.value(0).toInt();
    } catch (...) {
        qDebug() << "Error in queryAddRecipe";
        return -1;
    }
}

void Database::queryAddIngredient(int recipe_id, const QString &ingredient_name, const QString &quantity)
{
    try {
        QSqlQuery query;
        query.prepare("EXEC dbo.AddIngredient ?, ?, ?");
        query.bindValue(0, recipe_id);
        query.bindValue(1, ingredient_name);
        query.bindValue(2, quantity);
        query.exec();
    } catch (...) {
        qDebug() << "Error in queryAddIngredient";
    }
}

QStringList Database::queryGetUniqueCategories(int user_id)
{
    try {
        QStringList categories_list;
        QSqlQuery query;
        query.prepare("EXEC dbo.GetUniqueCategories ?");
        query.bindValue(0, user_id);
        query.exec();

        qDebug() << "here";
        qDebug() << query.value(0);
        while (query.next()) {
                 QString name = query.value(0).toString();
                 qDebug() << name;
                 categories_list.push_back(name);
        }
        return categories_list;
    } catch (...) {
        qDebug() << "Error in queryGetUniqueCategories";
        return {};
    }
}

QStringList Database::queryGetRecipeNamesByCategory(int user_id, const QString &category)
{
    try {
        QStringList recipes_list;

        QSqlQuery query;
        query.prepare("EXEC dbo.GetRecipeNamesByCategory ?, ?");
        query.bindValue(0, user_id);
        query.bindValue(1, category);
        query.exec();

//        qDebug() << "here";
//        qDebug() << query.value(0);
        while (query.next()) {
             qDebug() << query.value(0);
             QString name = query.value(0).toString();
             recipes_list.push_back(name);
        }

        return recipes_list;
    } catch (...) {
        qDebug() << "Error in queryGetRecipesByCategory";
        return {};
    }
}

void Database::queryCreateBackup(const QString &path)
{
    try {
        QSqlQuery query;
        query.prepare("EXEC dbo.CreateBackup ?");
        query.bindValue(0, path);
        query.exec();
    } catch (...) {
        qDebug() << "Error in queryCreateBackup";
    }
}

QString Database::queryGetRecipeByName(int user_id, const QString &recipe_name, const QString &category)
{
    QString str = "";
    try {
        QSqlQuery query;
        query.prepare("EXEC dbo.GetRecipeByName ?, ?, ?");
        query.bindValue(0, user_id);
        query.bindValue(1, recipe_name);
        query.bindValue(2, category);
        query.exec();

        query.next();
        str = "Калорий:" + query.value(0).toString() + "\n" +
                "Время приготовления : " + query.value(1).toString() + " минут\n\n" +
                "Описание рецепта:\n" + query.value(2).toString() + "\n";

        return str;
    } catch (...) {
        qDebug() << "Error in queryGetRecipeByName";
        return "";
    }}

QString Database::queryGetIngredientsByName(int user_id, const QString &recipe_name, const QString &category)
{
    QString str = "Ингредиенты:\n";
    try {
        QSqlQuery query;
        query.prepare("EXEC dbo.GetIngredientsByName ?, ?, ?");
        query.bindValue(0, user_id);
        query.bindValue(1, recipe_name);
        query.bindValue(2, category);
        query.exec();

        while (query.next()) {
            str += query.value(0).toString() + " " + query.value(1).toString() + "\n";
        }
        str += "\n";

        return str;
    } catch (...) {
        qDebug() << "Error in queryGetIngredientsByName";
        return "";
    }
}

void Database::queryDeleteRecipeByName(int user_id, const QString &recipe_name, const QString &category)
{
/*
        try {
        QSqlQuery query;
        query.prepare("EXEC dbo.GetIngredientsByName ?, ?, ?");
        query.bindValue(0, user_id);
        query.bindValue(1, recipe_name);
        query.bindValue(2, category);
        query.exec();

        while (query.next()) {
            str += query.value(0).toString() + " " + query.value(1).toString() + "\n";
        }
        str += "\n";

        return str;
    } catch (...) {
        qDebug() << "Error in queryGetIngredientsByName";
        return "";
    }
*/
}
