/********************************************************************************
** Form generated from reading UI file 'helpdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPDIALOG_H
#define UI_HELPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_helpDialog
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;

    void setupUi(QDialog *helpDialog)
    {
        if (helpDialog->objectName().isEmpty())
            helpDialog->setObjectName(QStringLiteral("helpDialog"));
        helpDialog->resize(417, 399);
        label = new QLabel(helpDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 30, 213, 134));
        layoutWidget = new QWidget(helpDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(140, 200, 211, 161));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font;
        font.setFamily(QString::fromUtf8("\353\247\221\354\235\200 \352\263\240\353\224\225"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_5->setFont(font);

        verticalLayout_2->addWidget(label_5);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);

        verticalLayout_2->addWidget(label_6);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);

        verticalLayout_2->addWidget(label_7);

        widget = new QWidget(helpDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(70, 200, 53, 161));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        verticalLayout->addWidget(label_4);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);


        retranslateUi(helpDialog);

        QMetaObject::connectSlotsByName(helpDialog);
    } // setupUi

    void retranslateUi(QDialog *helpDialog)
    {
        helpDialog->setWindowTitle(QApplication::translate("helpDialog", "Dialog", 0));
        label->setText(QApplication::translate("helpDialog", "TextLabel", 0));
        label_5->setText(QApplication::translate("helpDialog", "joeseungmo@gmail.com", 0));
        label_6->setText(QApplication::translate("helpDialog", "kuntae89@naver.com", 0));
        label_7->setText(QApplication::translate("helpDialog", "gksehd1004@naver.com", 0));
        label_2->setText(QApplication::translate("helpDialog", "\354\241\260\354\212\271\353\252\250", 0));
        label_4->setText(QApplication::translate("helpDialog", "\352\271\200\352\261\264\355\203\234", 0));
        label_3->setText(QApplication::translate("helpDialog", "\355\225\234\353\217\231\355\235\254", 0));
    } // retranslateUi

};

namespace Ui {
    class helpDialog: public Ui_helpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPDIALOG_H
