#-------------------------------------------------
#
# Project created by QtCreator 2014-06-19T23:46:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_LFLAGS += /INCREMENTAL:NO
TARGET = ShellUSB_v0_5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    encryptthread.cpp \
    progdialog.cpp \
    shellusb.cpp \
    tinyaes.cpp \
    settingdialog.cpp \
    logthread.cpp \
    setup.cpp \
    loadingdialog.cpp \
    helpdialog.cpp

HEADERS  += mainwindow.h \
    encryptthread.h \
    progdialog.h \
    shellusb.h \
    tinyaes.h \
    settingdialog.h \
    logthread.h \
    setup.h \
    loadingdialog.h \
    helpdialog.h

FORMS    += mainwindow.ui \
    progdialog.ui \
    shellusb.ui \
    settingdialog.ui \
    loadingdialog.ui \
    helpdialog.ui

RESOURCES += \
    img.qrc
