#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // меняю ui главного окна
    this->setWindowIcon(QIcon(":/icons/client_app_icon.png"));
    this->setWindowTitle("1234");
    ui->setupUi(this);


    // TODO: скрыть главное окно
//    this->hide();
//    this->setVisible(false);

    database = new Database();
    database->openDatabase();

    authorization();
}


void MainWindow::authorization()
{
    authDlg = new AuthorizationDialog(this);
    authDlg->setDatabase(database);

    this->setFocusProxy(authDlg);
    authDlg->show();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete database;
}
