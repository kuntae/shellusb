#include "encryptthread.h"

#include <QDebug>
#include <QApplication>

EncryptThread::EncryptThread(QObject *parent):
    QThread(parent)
{
    qDebug() << "thread created";
    this->stop = false;
}

void EncryptThread::init(QString filePath, QByteArray key, bool cryptFlag) {
    //qDebug() << "Thread: " << filePath << " " << key << " " << cryptFlag;
    this->filePath = filePath;
    this->key = key;
    this->cryptFlag = cryptFlag;
}

EncryptThread::~EncryptThread()
{
    qDebug() << "Thread die";
}

void EncryptThread::run()
{
    if (this->cryptFlag)
        encrypt();
    else
        decrypt();
}

void EncryptThread::encrypt()
{
    QMutex mutex;
    const int size = 128;

    // set a source file path
    QString srcPath = this->filePath;
    QFile srcFile(srcPath);

    // set a target file path
    QString tgtPath = srcPath + ".ShellUSB";
    QFile tgtFile(tgtPath);

    // set a key
    QByteArray key = this->key;

    // open a source file and target file
    if (!srcFile.open(QFile::ReadOnly))
    {
        qDebug() << "Could not open a read file";
        return;
    }

    if (!tgtFile.open(QFile::WriteOnly))
    {
        qDebug() << "Could not open a write file";
        return;
    }

    // set a buffer fixed size(128byte)
    QByteArray buffer;
    buffer.resize(size);

    QByteArray encrypted;

    int count = 0;
    int presentSize = 0;
    int onePercentSize = srcFile.size() / 100;
    int finalSize = onePercentSize;

    // read a source file and write a target file encrypted datas
    while (!srcFile.atEnd())
    {
        mutex.lock();
        if(this->stop) {
            break;
        }
        mutex.unlock();
        buffer = srcFile.read(size);
        encrypted = crypto.Encrypt(buffer, key);
        tgtFile.write(encrypted);

        // update a progressbar
        presentSize += buffer.size();

        if (presentSize > finalSize)
        {
            finalSize += onePercentSize;
            count++;
        }
        emit sinalUpdate(count);
    }

    // close and remove a source file
    srcFile.close();

    // flush and close a target file
    tgtFile.flush();
    tgtFile.close();

    // 비정상적으로 종료된 경우
    if(this->stop) {
        // target file을 삭제
        tgtFile.remove();
    }
    // 정상적으로 종료된 경우
    else {
        // source file을 삭제
        srcFile.remove();
    }
}

void EncryptThread::decrypt()
{
    QMutex mutex;
    const int size = 160;

    // set a source file path
    QString srcPath = this->filePath;
    QFile srcFile(srcPath);

    // set a target file path
    int firstDot = srcPath.indexOf(":");
    int lastDot = srcPath.lastIndexOf(".");
    QString tgtPath = srcPath.mid(firstDot - 1, lastDot + 1);
    QFile tgtFile(tgtPath);

    // set a key
    QByteArray key = this->key;

    // open a source file and target file
    if (!srcFile.open(QFile::ReadOnly))
    {
        qDebug() << "Could not open a read file";
        return;
    }

    if (!tgtFile.open(QFile::WriteOnly))
    {
        qDebug() << "Could not open a write file";
        return;
    }

    // set a buffer fixed size(160byte)
    QByteArray buffer;
    buffer.resize(size);

    QByteArray decrypted;

    int count = 0;
    int presentSize = 0;
    int onePercentSize = srcFile.size() / 100;
    int finalSize = onePercentSize;

    // read a source file and write a target file decrypted datas
    while (!srcFile.atEnd())
    {
        mutex.lock();
        if(this->stop) {
            break;
        }
        mutex.unlock();
        buffer = srcFile.read(size);
        decrypted = crypto.Decrypt(buffer, key);
        tgtFile.write(decrypted);

        // update a progressbar
        presentSize += buffer.size();

        if (presentSize > finalSize)
        {
            finalSize += onePercentSize;
            count++;
        }

        emit sinalUpdate(count);
    }

    // close and remove a source file
    srcFile.close();

    // flush and close a target file
    tgtFile.flush();
    tgtFile.close();

    // 비정상적으로 종료된 경우
    if(this->stop) {
        // target file을 삭제
        tgtFile.remove();
    }
    // 정상적으로 종료된 경우
    else {
        // source file을 삭제
        srcFile.remove();
    }
}

void EncryptThread::cancelThread()
{
    qDebug() << "call";

    return;
}
