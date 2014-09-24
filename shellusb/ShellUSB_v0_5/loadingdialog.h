#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDebug>
#include <QString>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QHash>

#include "logthread.h"
#include "tinyaes.h"
#include "setup.h"
#include "settingdialog.h"

namespace Ui {
class LoadingDialog;
}

class LoadingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadingDialog(QWidget *parent = 0);
    ~LoadingDialog();
    void chkSysDirectory();
    void chkShellusbFile();
    void chkShellpieceFile();
    void setLogFileName();
    void chkLogPeriod();
    void makeHash();
    void removeDirectory(const QString &src);
    qint64 getsize(const QString &src);

private:
    Ui::LoadingDialog *ui;
    QTimer time;
    const QString sysdir;
    const QString sysdirenc;
    const QString sysdirdec;
    const QString shellusb;
    const QString shellpiece;
    const QString shellhash;
    QString::iterator iter;
};

#endif // LOADINGDIALOG_H
