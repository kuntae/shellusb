#ifndef PROGDIALOG_H
#define PROGDIALOG_H

#include <QDialog>
#include <QStyleFactory>
#include "encryptthread.h"

namespace Ui {
class ProgDialog;
}

class ProgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgDialog(QWidget *parent = 0);
    ~ProgDialog();
    void init(QString filePath, QByteArray key, bool cryptFlag);

private slots:
    void updatePd(int);

    void on_cancel_clicked();

private:
    Ui::ProgDialog *ui;
    EncryptThread *encryptThread;

signals:

};

#endif // PROGDIALOG_H
