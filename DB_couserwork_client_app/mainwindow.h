#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    AuthorizationDialog *authDlg;
    Database *database;
};

#endif // MAINWINDOW_H
