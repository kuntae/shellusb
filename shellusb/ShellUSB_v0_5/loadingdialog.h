#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDebug>

#include "logthread.h"

namespace Ui {
class LoadingDialog;
}

class LoadingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadingDialog(QWidget *parent = 0);
    ~LoadingDialog();
    void setLogFileName();
private:
    Ui::LoadingDialog *ui;
    QTimer time;
};

#endif // LOADINGDIALOG_H
