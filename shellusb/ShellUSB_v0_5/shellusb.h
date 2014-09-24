#ifndef SHELLUSB_H
#define SHELLUSB_H

#include "encryptthread.h"
#include "tinyaes.h"
#include "progdialog.h"
#include "logthread.h"
#include "helpdialog.h"

#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <QDirModel>
#include <QMainWindow>
#include <QDir>
#include <QFileSystemModel>
#include <QString>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QInputDialog>
#include <list>
#include <vector>
#include <QStyleFactory>
#include <QTextCodec>
#include <QMenu>

namespace Ui {
class ShellUSB;
}

class ShellUSB : public QDialog
{
    Q_OBJECT

public:
    explicit ShellUSB(QWidget *parent = 0);
    ~ShellUSB();

private slots:
    void on_enc_btn_clicked();
    void on_dnc_btn_clicked();
    void on_back_btn_clicked();
    void on_front_btn_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_treeView_clicked(const QModelIndex &treeIndex);


    void on_tableView_customContextMenuRequested(const QPoint &pos);

    void on_help_btn_clicked();

private:
    TinyAES crypto;
    bool ok;
    Ui::ShellUSB *ui;
    QFileSystemModel* model;
    QDirModel *treeModel;       // treeView에 사용될 모델
    std::list<QString>* lt;
    std::list<QString>::reverse_iterator iter;

    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
};

#endif // SHELLUSB_H
