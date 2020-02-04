#include "registrationdialog.h"
#include "ui_registrationdialog.h"

RegistrationDialog::RegistrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationDialog)
{
    this->setWindowIcon(QIcon(":/icons/client_app_icon.png"));
    this->setWindowTitle("Регистрация");
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint); // делаю окно нересайзбл
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint); // удаляю знак вопроса из title bar'a

//    QPixmap bkgnd(":/backgorunds/back.jpg");
//    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
//    QPalette palette;
//    palette.setBrush(QPalette::Background, bkgnd);
//    this->setPalette(palette);

    ui->setupUi(this);
}

void RegistrationDialog::setDatabase(Database *db)
{
    database = db;
}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}

void RegistrationDialog::on_regBttn_clicked()
{
    QString login = ui->enterLoginLineEdit->text();
    QString pass1 = ui->enterPassLineEdit->text();
    QString pass2 = ui->confirmPassLineEdit->text();

    if (login.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите логин!");
        return;
    }

    if (pass1.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите пароль!");
        return;
    }

    if (pass1 != pass2) {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают!");
        qDebug() << pass1 << pass2;
        return;
    }

    bool ok = database->queryRegistration(login, pass1, 1);
    if (ok) {
        QMessageBox::information(this, "Успех", "Вы успешно зарегистрировались!");
        this->close();
    }
    else
        QMessageBox::warning(this, "Ошибка", "Такой пользователь уже есть");


    // TODO: добавить лог о добавлении пользователя в БД
}
