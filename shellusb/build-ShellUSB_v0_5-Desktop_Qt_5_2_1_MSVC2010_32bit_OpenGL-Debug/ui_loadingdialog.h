/********************************************************************************
** Form generated from reading UI file 'loadingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADINGDIALOG_H
#define UI_LOADINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_LoadingDialog
{
public:
    QLabel *label;
    QLabel *text_label;

    void setupUi(QDialog *LoadingDialog)
    {
        if (LoadingDialog->objectName().isEmpty())
            LoadingDialog->setObjectName(QStringLiteral("LoadingDialog"));
        LoadingDialog->resize(827, 437);
        LoadingDialog->setCursor(QCursor(Qt::ArrowCursor));
        label = new QLabel(LoadingDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 827, 437));
        label->setCursor(QCursor(Qt::ArrowCursor));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/Lighthouse.png")));
        text_label = new QLabel(LoadingDialog);
        text_label->setObjectName(QStringLiteral("text_label"));
        text_label->setGeometry(QRect(10, 405, 321, 21));
        QFont font;
        font.setFamily(QStringLiteral("Monaco"));
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        text_label->setFont(font);

        retranslateUi(LoadingDialog);

        QMetaObject::connectSlotsByName(LoadingDialog);
    } // setupUi

    void retranslateUi(QDialog *LoadingDialog)
    {
        LoadingDialog->setWindowTitle(QApplication::translate("LoadingDialog", "Dialog", 0));
        label->setText(QString());
        text_label->setText(QApplication::translate("LoadingDialog", "Starting ShellUSB...", 0));
    } // retranslateUi

};

namespace Ui {
    class LoadingDialog: public Ui_LoadingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADINGDIALOG_H
