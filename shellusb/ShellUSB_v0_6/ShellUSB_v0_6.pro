#-------------------------------------------------
#
# Project created by QtCreator 2014-06-19T23:46:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShellUSB_v0_6
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    encryptthread.cpp \
    progdialog.cpp \
    shellusb.cpp \
    tinyaes.cpp \
    settingdialog.cpp

HEADERS  += mainwindow.h \
    encryptthread.h \
    progdialog.h \
    shellusb.h \
    tinyaes.h \
    settingdialog.h

FORMS    += mainwindow.ui \
    progdialog.ui \
    shellusb.ui \
    settingdialog.ui
