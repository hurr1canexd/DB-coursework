#ifndef DATABASE_H
#define DATABASE_H
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QList>
#include <QString>
#include <QStringList>

class Database
{
public:
    QList<QString> recipes;

    bool openDatabase();
    bool queryRegistration(const QString &login, const QString &pass, int access_level);
    int queryAuthorization(const QString &login, const QString &pass);
    QString queryGetLoginById(const int user_id);
    int queryAddRecipe(const QString& recipe_name, const QString& category, int calorie,
                        const QString& recipe_description, int cooking_time, int user_id);
    void queryAddIngredient(int recipe_id, const QString& ingredient_name, const QString& quantity);
    QStringList queryGetUniqueCategories(int user_id);
    QStringList queryGetRecipeNamesByCategory(int user_id, const QString& category);
    void queryCreateBackup(const QString &path);
    QString queryGetRecipeByName(int user_id, const QString& recipe_name, const QString& category);
    QString queryGetIngredientsByName(int user_id, const QString& recipe_name, const QString& category);
    void queryDeleteRecipeByName(int user_id, const QString& recipe_name, const QString& category);
};

#endif // DATABASE_H
