#include "mainwindow.h"
#include "authorizationdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    AuthorizationDialog auth_dlg;
//    auth_dlg.show();

    MainWindow w;
    w.show();

    return a.exec();
}
