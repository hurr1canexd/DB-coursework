#ifndef ADDRECIPEDIALOG_H
#define ADDRECIPEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QStringList>
#include "database.h"

namespace Ui {
class AddRecipeDialog;
}

class AddRecipeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecipeDialog(QWidget *parent = 0);
    void setDatabase(Database *db);
    void setUserId(int _user_id);
    ~AddRecipeDialog();

private slots:
    void on_add_recipe_Btn_clicked();

    void on_plus_Btn_clicked();

    void on_minus_Btn_clicked();

private:
    Ui::AddRecipeDialog *ui;
    Database *database;
    int user_id, recipe_id, calorie, cooking_time;
    QString recipe_name, category, recipe_description;

    void getDataFromUi();
};

#endif // ADDRECIPEDIALOG_H
