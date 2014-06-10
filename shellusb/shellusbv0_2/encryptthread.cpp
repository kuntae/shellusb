#include "encryptthread.h"
#include <QDebug>
#include <QApplication>

EncryptThread::EncryptThread(QString path, QByteArray key, bool cryptflag):
    target(path), key(key), cryptflag(cryptflag)
{
    w = new QWidget();
    pd = new progdialog(w);
    connect(this, SIGNAL(changeNumber(int)), pd, SLOT(onChangeNumber(int)));
    pd->show();
}

EncryptThread::~EncryptThread()
{
    delete pd;
    delete w;
    qDebug() << "Thread die";
}

void EncryptThread::run()
{
    if (this->cryptflag)
        encrypt();
    else
        decrypt();
}

void EncryptThread::encrypt()
{
    const int size = 128;

    QString srcpath = this->target;
    QFile srcfile(srcpath);

    QString tgtpath = srcpath + ".shellUSB";
    QFile tgtfile(tgtpath);

    QByteArray key = this->key;

    if (!srcfile.open(QFile::ReadOnly))
    {
        qDebug() << "Could not open read file";
        return;
    }

    if (!tgtfile.open(QFile::WriteOnly))
    {
        qDebug() << "Could not open write file";
        return;
    }

    QByteArray buffer;
    buffer.resize(size);

    QByteArray encrypted;

    int i = 0;
    while (!srcfile.atEnd())
    {
        buffer = srcfile.read(size);
        encrypted = crypto.Encrypt(buffer, key);
        tgtfile.write(encrypted);
        emit changeNumber(i);
        i++;
    }

    srcfile.close();
    srcfile.remove();

    tgtfile.flush();
    tgtfile.close();
}

void EncryptThread::decrypt()
{
    const int size = 160;

    QString srcpath = this->target;
    QFile srcfile(srcpath);

    int firstdot = srcpath.indexOf(":");
    int lastdot = srcpath.lastIndexOf(".");
    QString tgtpath = srcpath.mid(firstdot - 1, lastdot + 1);
    QFile tgtfile(tgtpath);

    QByteArray key = this->key;

    if (!srcfile.open(QFile::ReadOnly))
    {
        qDebug() << "Could not open read file";
        return;
    }

    if (!tgtfile.open(QFile::WriteOnly))
    {
        qDebug() << "Could not open write file";
        return;
    }

    QByteArray buffer;
    buffer.resize(size);

    QByteArray decrypted;

    while (!srcfile.atEnd())
    {
        buffer = srcfile.read(size);
        decrypted = crypto.Decrypt(buffer, key);
        tgtfile.write(decrypted);
    }

    srcfile.close();
    srcfile.remove();

    tgtfile.flush();
    tgtfile.close();
}
