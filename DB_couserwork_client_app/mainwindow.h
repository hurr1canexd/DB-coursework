#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "authorizationdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void authorization();
    ~MainWindow();

public slots:
    void startClientWork(User);

private slots:
    void on_action_exit_triggered();
    void on_action_help_triggered();
    void on_action_about_triggered();

private:
    Ui::MainWindow *ui;
    AuthorizationDialog *authDlg;
    Database *database;
};

#endif // MAINWINDOW_H
