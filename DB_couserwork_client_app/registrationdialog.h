#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QDialog>
#include <QCryptographicHash>
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>
#include "database.h"

namespace Ui {
class RegistrationDialog;
}

class RegistrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDialog(QWidget *parent = 0);
    void setDatabase(Database *db);
    ~RegistrationDialog();

private slots:
    void on_regBttn_clicked();

private:
    Ui::RegistrationDialog *ui;
    Database *database;
};

#endif // REGISTRATIONDIALOG_H
