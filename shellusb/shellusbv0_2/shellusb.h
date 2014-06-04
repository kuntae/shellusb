#ifndef SHELLUSB_H
#define SHELLUSB_H

#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <QDirModel>
#include <QDir>
#include <QFileSystemModel>
#include <QString>
#include <QDesktopServices>
#include <QUrl>

#include <list>
#include <vector>

#include "encryptthread.h"

namespace Ui {
class shellusb;
}

class shellusb : public QDialog
{
    Q_OBJECT

public:
    explicit shellusb(QWidget *parent = 0);
    ~shellusb();

private slots:
    void on_enc_btn_clicked();

    void on_dnc_btn_clicked();

    void on_back_btn_clicked();

    void on_front_btn_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::shellusb *ui;
    QFileSystemModel* model;
    std::list<QString>* lt;
    std::list<QString>::reverse_iterator iter;
};

#endif // SHELLUSB_H
