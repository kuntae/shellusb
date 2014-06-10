#ifndef ENCRYPTTHREAD_H
#define ENCRYPTTHREAD_H

#include <QThread>
#include <QString>
#include <QtCore>
#include <QProgressBar>

#include "tinyaes.h"
#include "progdialog.h"

class EncryptThread : public QThread
{
public:
    explicit EncryptThread(QString path, QByteArray key, bool cryptflag);
    ~EncryptThread();

protected:
    void run();
    void encrypt();
    void decrypt();

private:
    TinyAES crypto;
    QString target;
    QByteArray key;
    bool cryptflag;
    QWidget *w;
    progdialog *pd;

signals:
    void changeNumber(int i);

};

#endif // ENCRYPTTHREAD_H
