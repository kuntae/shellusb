/********************************************************************************
** Form generated from reading UI file 'shellusb.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHELLUSB_H
#define UI_SHELLUSB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShellUSB
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *enc_btn;
    QPushButton *dnc_btn;
    QTableView *tableView;
    QPushButton *help_btn;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *back_btn;
    QPushButton *front_btn;
    QTreeView *treeView;
    QToolButton *toolButton;
    QToolButton *toolButton_2;

    void setupUi(QDialog *ShellUSB)
    {
        if (ShellUSB->objectName().isEmpty())
            ShellUSB->setObjectName(QStringLiteral("ShellUSB"));
        ShellUSB->resize(686, 444);
        layoutWidget = new QWidget(ShellUSB);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 410, 661, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        enc_btn = new QPushButton(layoutWidget);
        enc_btn->setObjectName(QStringLiteral("enc_btn"));

        horizontalLayout->addWidget(enc_btn);

        dnc_btn = new QPushButton(layoutWidget);
        dnc_btn->setObjectName(QStringLiteral("dnc_btn"));

        horizontalLayout->addWidget(dnc_btn);

        tableView = new QTableView(ShellUSB);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(250, 40, 421, 361));
        tableView->setDragDropMode(QAbstractItemView::DragDrop);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        help_btn = new QPushButton(ShellUSB);
        help_btn->setObjectName(QStringLiteral("help_btn"));
        help_btn->setGeometry(QRect(606, 0, 31, 20));
        layoutWidget_2 = new QWidget(ShellUSB);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 10, 134, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        back_btn = new QPushButton(layoutWidget_2);
        back_btn->setObjectName(QStringLiteral("back_btn"));

        horizontalLayout_2->addWidget(back_btn);

        front_btn = new QPushButton(layoutWidget_2);
        front_btn->setObjectName(QStringLiteral("front_btn"));

        horizontalLayout_2->addWidget(front_btn);

        treeView = new QTreeView(ShellUSB);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(10, 40, 231, 361));
        toolButton = new QToolButton(ShellUSB);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(660, 0, 27, 18));
        toolButton_2 = new QToolButton(ShellUSB);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setGeometry(QRect(635, 0, 27, 18));

        retranslateUi(ShellUSB);

        QMetaObject::connectSlotsByName(ShellUSB);
    } // setupUi

    void retranslateUi(QDialog *ShellUSB)
    {
        ShellUSB->setWindowTitle(QApplication::translate("ShellUSB", "Dialog", 0));
        enc_btn->setText(QApplication::translate("ShellUSB", "Enc", 0));
        dnc_btn->setText(QApplication::translate("ShellUSB", "Dec", 0));
        help_btn->setText(QString());
        back_btn->setText(QString());
        front_btn->setText(QString());
        toolButton->setText(QApplication::translate("ShellUSB", "X", 0));
        toolButton_2->setText(QApplication::translate("ShellUSB", "_", 0));
    } // retranslateUi

};

namespace Ui {
    class ShellUSB: public Ui_ShellUSB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHELLUSB_H
