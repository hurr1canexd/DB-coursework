#include "mainwindow.h"
#include "authorizationdialog.h"
#include <QApplication>
#include <QDialog>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AuthorizationDialog auth_dlg;
    if (auth_dlg.exec() != QDialog::Accepted) {
        qDebug() << QDialog::Accepted;
        return 0;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
