#include "authorizationdialog.h"
#include "ui_authorizationdialog.h"


AuthorizationDialog::AuthorizationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationDialog)
{
    this->setWindowIcon(QIcon(":/icons/client_app_icon.png"));
    this->setWindowTitle("КЛУБ BOY$");

    ui->setupUi(this);
}


void AuthorizationDialog::setDatabase(Database *db)
{
    database = db;
}


AuthorizationDialog::~AuthorizationDialog()
{
    delete ui;
}

void AuthorizationDialog::on_authBtn_clicked()
{

}
