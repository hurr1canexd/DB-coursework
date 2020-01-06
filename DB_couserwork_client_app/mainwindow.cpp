#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // меняю ui главного окна
    this->setWindowIcon(QIcon(":/icons/client_app_icon.png"));
    this->setWindowTitle("Кулинарная книга");
    ui->setupUi(this);


    // TODO: скрыть главное окно
//    this->hide();
//    this->setVisible(false);

//    database = new Database();
//    database->openDatabase();

    authorization();
}


void MainWindow::authorization()
{
//    authDlg = new AuthorizationDialog(this);
//    authDlg->setDatabase(database);

//    this->setFocusProxy(authDlg);
//    connect(authDlg, SIGNAL(autorizationOk(User)), this, SLOT(startClientWork(User)));
//    authDlg->show();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete database;
}

void MainWindow::startClientWork(User user)
{
    this->ui->userLabel->setText(user.getLogin());
}

void MainWindow::on_action_exit_triggered()
{
    this->close();
}

void MainWindow::on_action_help_triggered()
{
    QMessageBox::about(this, "Помощь", "Книга кулинарных рецептов");
}

void MainWindow::on_action_about_triggered()
{
    QMessageBox::about(this, "О программе", "Программа была слеплена одним загадочным студентом МАТИ.)");
}
