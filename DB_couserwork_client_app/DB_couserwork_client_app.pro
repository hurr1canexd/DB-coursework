#-------------------------------------------------
#
# Project created by QtCreator 2020-01-03T18:37:19
#
#-------------------------------------------------

QT       += core gui
QT       += sql
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DB_couserwork_client_app
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    authorizationdialog.cpp \
    database.cpp \
    user.cpp \
    registrationdialog.cpp \
    addrecipedialog.cpp

HEADERS  += mainwindow.h \
    authorizationdialog.h \
    database.h \
    user.h \
    registrationdialog.h \
    addrecipedialog.h

FORMS    += mainwindow.ui \
    authorizationdialog.ui \
    registrationdialog.ui \
    addrecipedialog.ui

RESOURCES += \
    resources.qrc
