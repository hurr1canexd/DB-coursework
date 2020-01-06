#ifndef AUTHORIZATIONDIALOG_H
#define AUTHORIZATIONDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QCryptographicHash>
#include "user.h"
#include "database.h"
#include "registrationdialog.h"
//#include "mainwindow.h"


namespace Ui {
class AuthorizationDialog;
}

class AuthorizationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationDialog(QWidget *parent = 0);
    void setDatabase(Database *db);
    ~AuthorizationDialog();
    QString getInfo(QString str) {
        return "";
    }

signals:
    void autorizationOk(User);

private slots:
    void on_authBtn_clicked();
    void on_regBtn_clicked();

private:
    Ui::AuthorizationDialog *ui;
//    MainWindow *mw;
    Database *database;
    RegistrationDialog *regDlg;

};

#endif // AUTHORIZATIONDIALOG_H
