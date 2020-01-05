#ifndef AUTHORIZATIONDIALOG_H
#define AUTHORIZATIONDIALOG_H

#include <QDialog>
#include <QLabel>
#include "database.h"

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

private slots:
    void on_authBtn_clicked();

private:
    Ui::AuthorizationDialog *ui;
    Database *database;
};

#endif // AUTHORIZATIONDIALOG_H
