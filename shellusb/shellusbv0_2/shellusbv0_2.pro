#-------------------------------------------------
#
# Project created by QtCreator 2014-06-04T14:01:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shellusbv0_2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    progdialog.cpp \
    shellusb.cpp \
    tinyaes.cpp \
    encryptthread.cpp \
    filecontrol.cpp

HEADERS  += mainwindow.h \
    progdialog.h \
    shellusb.h \
    tinyaes.h \
    encryptthread.h \
    filecontrol.h

FORMS    += mainwindow.ui \
    progdialog.ui \
    shellusb.ui
