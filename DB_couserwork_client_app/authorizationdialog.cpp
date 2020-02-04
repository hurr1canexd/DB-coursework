#include "authorizationdialog.h"
#include "ui_authorizationdialog.h"


AuthorizationDialog::AuthorizationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationDialog)
{
    this->setWindowIcon(QIcon(":/icons/client_app_icon.png"));
    this->setWindowTitle("Авторизация");
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint); // делаю окно нересайзбл
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint); // удаляю знак вопроса из title bar'a
//    this->setModal(true); // делаю диалог модальным
//    this->ui->regBtn->setStyleSheet("color: red");

    ui->setupUi(this);

    //connect(this, SIGNAL(autorizationOk(User)), mw, SLOT(startClientWork(User)));
//    database = new Database();
//    database->openDatabase();
//    this->setDatabase(database);

    regDlg = new RegistrationDialog(this);
    regDlg->hide();
}


void AuthorizationDialog::setDatabase(Database *db)
{
    database = db;
}


AuthorizationDialog::~AuthorizationDialog()
{
    delete ui;
    //    delete regDlg;
}

int AuthorizationDialog::getUserId()
{
    return user_id;
}


void AuthorizationDialog::on_authBtn_clicked()
{
    QString login = ui->loginLineEdit->text().trimmed();
    QString pass = ui->passLineEdit->text();

    if (login.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите логин!");
        return;
    }

    if (pass.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите пароль!");
        return;
    }

    QString encoded_pass = QString(QCryptographicHash::hash(pass.toLocal8Bit(), QCryptographicHash::Md5).toHex());

    qDebug() << login << pass << encoded_pass;

    user_id = database->queryAuthorization(login, pass);

    if (user_id == -1) {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль!");
    } else {
        emit autorizationOk(User(1, login));
        QMessageBox::information(this, "Всё ок", "Авторизация прошла успешно!");
        this->done(1);
        this->close();
        regDlg->close();
    }
}


void AuthorizationDialog::on_regBtn_clicked()
{
    regDlg->show();
}
