#include "mainwindow.h"
#include "authorizationdialog.h"
#include "database.h"
#include <QApplication>
#include <QDialog>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int user_id;
    Database *db;
    db->openDatabase();

    AuthorizationDialog auth_dlg;
    auth_dlg.setDatabase(db);
    MainWindow w;

    if (auth_dlg.exec() != QDialog::Accepted) {
        return 0;
    } else {
        user_id = auth_dlg.getUserId();
        w.setUserId(user_id);
        w.is_first_authorization = false;
        w.fillUi();
    }

    w.show();

    return a.exec();
}
