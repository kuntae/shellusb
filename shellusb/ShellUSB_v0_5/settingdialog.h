#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTextStream>

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

private slots:
    void on_pushButton_3_clicked();

    void on_log_use_clicked();

    void on_log_not_use_clicked();

signals:
    void noMatchPwd();
private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
