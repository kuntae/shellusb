/********************************************************************************
** Form generated from reading UI file 'progdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGDIALOG_H
#define UI_PROGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_progdialog
{
public:
    QProgressBar *progressBar;
    QPushButton *pushButton;

    void setupUi(QDialog *progdialog)
    {
        if (progdialog->objectName().isEmpty())
            progdialog->setObjectName(QStringLiteral("progdialog"));
        progdialog->resize(386, 96);
        progressBar = new QProgressBar(progdialog);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 20, 381, 23));
        progressBar->setValue(0);
        progressBar->setTextVisible(true);
        progressBar->setOrientation(Qt::Horizontal);
        pushButton = new QPushButton(progdialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(280, 60, 75, 23));

        retranslateUi(progdialog);

        QMetaObject::connectSlotsByName(progdialog);
    } // setupUi

    void retranslateUi(QDialog *progdialog)
    {
        progdialog->setWindowTitle(QApplication::translate("progdialog", "Dialog", 0));
        pushButton->setText(QApplication::translate("progdialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class progdialog: public Ui_progdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGDIALOG_H
