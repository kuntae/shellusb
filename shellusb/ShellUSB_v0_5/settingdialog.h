#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QStyleFactory>
#include <QFileDialog>
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
    void on_log_use_clicked();

    void on_log_not_use_clicked();

    void on_encpath_btn_clicked();

    void on_decpath_btn_clicked();

    void on_submit_btn_clicked();

signals:
    void noMatchPwd();
private:
    Ui::SettingDialog *ui;
    QString firstPwd;
    QString secondPwd;
    QString encUrl;
    QString decUrl;
    QString pwdchk;
    QString encrypt;
    QString flag;
    QString period;
};

#endif // SETTINGDIALOG_H
