#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QList>
#include <QString>
#include <QVector>
#include <QStandardItemModel>
#include <QSqlQueryModel>
#include <QStringListModel>
#include <QInputDialog>
#include <QDir>
#include "authorizationdialog.h"
#include "addrecipedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool is_first_authorization = true;

    explicit MainWindow(QWidget *parent = nullptr);
    void setUserId(int user_id);
    void fillUi();
    ~MainWindow();

public slots:
    void startClientWork(User);

private slots:
    void on_action_exit_triggered();
    void on_action_help_triggered();
    void on_action_about_triggered();
    void on_action_enter_triggered();
    void on_show_add_recipe_dlg_Btn_clicked();
    void on_action_backup_triggered();
    void on_show_recipes_Btn_clicked();
    void on_show_cur_recipe_Btn_clicked();
    void on_del_Btn_clicked();

private:
    Ui::MainWindow *ui;
    Database *database;
    AuthorizationDialog *authDlg;
    AddRecipeDialog *addRecDlg;
    int user_id;
    QStringList categories;
    QVector<QStandardItem*> nodes;

    void authorization();
    void setStandart();
    void addRecipe();
    void buildTree();
};

#endif // MAINWINDOW_H
