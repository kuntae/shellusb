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
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_shellusb
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

    void setupUi(QDialog *shellusb)
    {
        if (shellusb->objectName().isEmpty())
            shellusb->setObjectName(QStringLiteral("shellusb"));
        shellusb->resize(686, 450);
        layoutWidget = new QWidget(shellusb);
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

        tableView = new QTableView(shellusb);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(250, 40, 421, 361));
        tableView->setDragDropMode(QAbstractItemView::DragDrop);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        help_btn = new QPushButton(shellusb);
        help_btn->setObjectName(QStringLiteral("help_btn"));
        help_btn->setGeometry(QRect(630, 10, 40, 23));
        layoutWidget_2 = new QWidget(shellusb);
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

        treeView = new QTreeView(shellusb);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(10, 40, 231, 361));

        retranslateUi(shellusb);

        QMetaObject::connectSlotsByName(shellusb);
    } // setupUi

    void retranslateUi(QDialog *shellusb)
    {
        shellusb->setWindowTitle(QApplication::translate("shellusb", "Dialog", 0));
        enc_btn->setText(QApplication::translate("shellusb", "Enc", 0));
        dnc_btn->setText(QApplication::translate("shellusb", "Dec", 0));
        help_btn->setText(QString());
        back_btn->setText(QString());
        front_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class shellusb: public Ui_shellusb {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHELLUSB_H
