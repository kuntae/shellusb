/********************************************************************************
** Form generated from reading UI file 'settingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *enc_url;
    QLineEdit *dec_url;
    QPushButton *encpath_btn;
    QPushButton *decpath_btn;
    QRadioButton *aes_128;
    QRadioButton *aes_256;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *language;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *password;
    QLineEdit *password_2;
    QLabel *label_7;
    QLabel *label_8;
    QComboBox *log_period;
    QComboBox *file_system;
    QLabel *label_9;
    QPushButton *submit_btn;
    QRadioButton *log_use;
    QRadioButton *log_not_use;
    QLabel *label_10;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName(QStringLiteral("SettingDialog"));
        SettingDialog->resize(410, 342);
        label = new QLabel(SettingDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(39, 23, 56, 12));
        label_2 = new QLabel(SettingDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(39, 53, 56, 12));
        enc_url = new QLineEdit(SettingDialog);
        enc_url->setObjectName(QStringLiteral("enc_url"));
        enc_url->setGeometry(QRect(99, 19, 231, 20));
        dec_url = new QLineEdit(SettingDialog);
        dec_url->setObjectName(QStringLiteral("dec_url"));
        dec_url->setGeometry(QRect(99, 49, 231, 20));
        encpath_btn = new QPushButton(SettingDialog);
        encpath_btn->setObjectName(QStringLiteral("encpath_btn"));
        encpath_btn->setGeometry(QRect(339, 17, 51, 23));
        decpath_btn = new QPushButton(SettingDialog);
        decpath_btn->setObjectName(QStringLiteral("decpath_btn"));
        decpath_btn->setGeometry(QRect(339, 47, 51, 23));
        aes_128 = new QRadioButton(SettingDialog);
        buttonGroup = new QButtonGroup(SettingDialog);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(aes_128);
        aes_128->setObjectName(QStringLiteral("aes_128"));
        aes_128->setGeometry(QRect(109, 93, 90, 16));
        aes_128->setChecked(true);
        aes_256 = new QRadioButton(SettingDialog);
        buttonGroup->addButton(aes_256);
        aes_256->setObjectName(QStringLiteral("aes_256"));
        aes_256->setGeometry(QRect(209, 93, 90, 16));
        label_3 = new QLabel(SettingDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(24, 93, 71, 20));
        label_4 = new QLabel(SettingDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(64, 133, 31, 16));
        language = new QComboBox(SettingDialog);
        language->setObjectName(QStringLiteral("language"));
        language->setGeometry(QRect(99, 130, 76, 22));
        language->setLayoutDirection(Qt::RightToLeft);
        label_5 = new QLabel(SettingDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(39, 173, 56, 12));
        label_6 = new QLabel(SettingDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(14, 203, 81, 20));
        password = new QLineEdit(SettingDialog);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(99, 168, 161, 20));
        password->setEchoMode(QLineEdit::Password);
        password_2 = new QLineEdit(SettingDialog);
        password_2->setObjectName(QStringLiteral("password_2"));
        password_2->setGeometry(QRect(99, 203, 161, 20));
        password_2->setEchoMode(QLineEdit::Password);
        label_7 = new QLabel(SettingDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 240, 81, 16));
        label_8 = new QLabel(SettingDialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 273, 111, 20));
        log_period = new QComboBox(SettingDialog);
        log_period->setObjectName(QStringLiteral("log_period"));
        log_period->setGeometry(QRect(120, 270, 76, 22));
        log_period->setLayoutDirection(Qt::RightToLeft);
        file_system = new QComboBox(SettingDialog);
        file_system->setObjectName(QStringLiteral("file_system"));
        file_system->setGeometry(QRect(119, 303, 76, 22));
        file_system->setLayoutDirection(Qt::RightToLeft);
        label_9 = new QLabel(SettingDialog);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(29, 306, 61, 16));
        submit_btn = new QPushButton(SettingDialog);
        submit_btn->setObjectName(QStringLiteral("submit_btn"));
        submit_btn->setGeometry(QRect(309, 303, 75, 23));
        log_use = new QRadioButton(SettingDialog);
        buttonGroup_2 = new QButtonGroup(SettingDialog);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(log_use);
        log_use->setObjectName(QStringLiteral("log_use"));
        log_use->setGeometry(QRect(100, 240, 51, 16));
        log_use->setChecked(true);
        log_not_use = new QRadioButton(SettingDialog);
        buttonGroup_2->addButton(log_not_use);
        log_not_use->setObjectName(QStringLiteral("log_not_use"));
        log_not_use->setGeometry(QRect(150, 240, 101, 16));
        label_10 = new QLabel(SettingDialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(210, 276, 56, 12));

        retranslateUi(SettingDialog);

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QApplication::translate("SettingDialog", "Dialog", 0));
        label->setText(QApplication::translate("SettingDialog", "enc \352\262\275\353\241\234", 0));
        label_2->setText(QApplication::translate("SettingDialog", "dec \352\262\275\353\241\234", 0));
        encpath_btn->setText(QApplication::translate("SettingDialog", "\353\263\200\352\262\275", 0));
        decpath_btn->setText(QApplication::translate("SettingDialog", "\353\263\200\352\262\275", 0));
        aes_128->setText(QApplication::translate("SettingDialog", "AES-128", 0));
        aes_256->setText(QApplication::translate("SettingDialog", "AES-256", 0));
        label_3->setText(QApplication::translate("SettingDialog", "\354\225\224\355\230\270\355\231\224 \353\260\251\354\213\235", 0));
        label_4->setText(QApplication::translate("SettingDialog", "\354\226\270\354\226\264", 0));
        language->clear();
        language->insertItems(0, QStringList()
         << QApplication::translate("SettingDialog", "Korean", 0)
         << QApplication::translate("SettingDialog", "English", 0)
        );
        label_5->setText(QApplication::translate("SettingDialog", "\353\271\204\353\260\200\353\262\210\355\230\270", 0));
        label_6->setText(QApplication::translate("SettingDialog", "\353\271\204\353\260\200\353\262\210\355\230\270 \355\231\225\354\235\270", 0));
        label_7->setText(QApplication::translate("SettingDialog", "\354\202\254\354\232\251\352\270\260\353\241\235 \354\240\200\354\236\245", 0));
        label_8->setText(QApplication::translate("SettingDialog", "\354\202\254\354\232\251\352\270\260\353\241\235 \354\225\214\353\246\274", 0));
        log_period->clear();
        log_period->insertItems(0, QStringList()
         << QApplication::translate("SettingDialog", "1", 0)
         << QApplication::translate("SettingDialog", "5", 0)
         << QApplication::translate("SettingDialog", "No Notice", 0)
        );
        label_9->setText(QApplication::translate("SettingDialog", "\355\214\214\354\235\274\354\213\234\354\212\244\355\205\234", 0));
        submit_btn->setText(QApplication::translate("SettingDialog", "\355\231\225\354\235\270", 0));
        log_use->setText(QApplication::translate("SettingDialog", "\354\202\254\354\232\251", 0));
        log_not_use->setText(QApplication::translate("SettingDialog", "\354\202\254\354\232\251\355\225\230\354\247\200 \354\225\212\354\235\214", 0));
        label_10->setText(QApplication::translate("SettingDialog", "MB", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
