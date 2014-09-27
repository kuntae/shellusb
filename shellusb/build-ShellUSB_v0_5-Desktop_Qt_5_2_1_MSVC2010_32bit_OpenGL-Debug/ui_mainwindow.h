/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *login_btn;
    QLineEdit *password;
    QLineEdit *lineEdit;
    QLabel *cacha_label;
    QPushButton *refresh_btn;
    QLabel *msg_label;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(287, 237);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        login_btn = new QPushButton(centralWidget);
        login_btn->setObjectName(QStringLiteral("login_btn"));
        login_btn->setGeometry(QRect(110, 180, 81, 23));
        password = new QLineEdit(centralWidget);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(60, 40, 161, 21));
        password->setEchoMode(QLineEdit::Password);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(29, 151, 161, 20));
        cacha_label = new QLabel(centralWidget);
        cacha_label->setObjectName(QStringLiteral("cacha_label"));
        cacha_label->setGeometry(QRect(20, 70, 251, 71));
        refresh_btn = new QPushButton(centralWidget);
        refresh_btn->setObjectName(QStringLiteral("refresh_btn"));
        refresh_btn->setGeometry(QRect(200, 150, 51, 23));
        msg_label = new QLabel(centralWidget);
        msg_label->setObjectName(QStringLiteral("msg_label"));
        msg_label->setGeometry(QRect(20, 200, 241, 16));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        login_btn->setText(QApplication::translate("MainWindow", "login", 0));
        cacha_label->setText(QApplication::translate("MainWindow", "Label", 0));
        refresh_btn->setText(QApplication::translate("MainWindow", "Refresh", 0));
        msg_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
