#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QStyleFactory>
#include "tinyaes.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();
    void writeSysFile();
    void writePwdFile();

private slots:
    void on_pushButton_3_clicked();

    void on_log_use_clicked();

    void on_log_not_use_clicked();

signals:
    void noMatchPwd();
private:
    Ui::SettingDialog *ui;
    QString firstPwd;
    QString secondPwd;
    QString encUrl;
    QString decUrl;
    QString lang;
    QString encrypt;
    QString flag;
    QString period;
};

#endif // SETTINGDIALOG_H
