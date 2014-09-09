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

class Ui_ProgDialog
{
public:
    QProgressBar *progressBar;
    QPushButton *cancel;

    void setupUi(QDialog *ProgDialog)
    {
        if (ProgDialog->objectName().isEmpty())
            ProgDialog->setObjectName(QStringLiteral("ProgDialog"));
        ProgDialog->resize(386, 96);
        progressBar = new QProgressBar(ProgDialog);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 20, 381, 23));
        progressBar->setValue(0);
        progressBar->setTextVisible(true);
        progressBar->setOrientation(Qt::Horizontal);
        cancel = new QPushButton(ProgDialog);
        cancel->setObjectName(QStringLiteral("cancel"));
        cancel->setEnabled(true);
        cancel->setGeometry(QRect(280, 60, 75, 23));

        retranslateUi(ProgDialog);

        QMetaObject::connectSlotsByName(ProgDialog);
    } // setupUi

    void retranslateUi(QDialog *ProgDialog)
    {
        ProgDialog->setWindowTitle(QApplication::translate("ProgDialog", "Dialog", 0));
        cancel->setText(QApplication::translate("ProgDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class ProgDialog: public Ui_ProgDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGDIALOG_H
