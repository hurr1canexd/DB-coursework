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

    ui->setupUi(this);

    //connect(this, SIGNAL(autorizationOk(User)), mw, SLOT(startClientWork(User)));
    database = new Database();
    database->openDatabase();
    this->setDatabase(database);

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


void AuthorizationDialog::on_authBtn_clicked()
{
    QString login = ui->loginLineEdit->text();
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

    int access_level = database->queryAuthorization(login, pass);

    if (access_level == 2) {
        QMessageBox::warning(this, "Ошибка", "Используйте админское приложение!");
    } else if (access_level == 1) {
        emit autorizationOk(User(1, login));
        QMessageBox::information(this, "Всё ок", "Авторизация прошла успешно!");
        this->done(1);
        this->close();
        regDlg->close();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неправильный логин или пароль!");
    }
}


void AuthorizationDialog::on_regBtn_clicked()
{
    regDlg->show();
}
