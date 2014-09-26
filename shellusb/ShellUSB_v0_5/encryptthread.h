#ifndef ENCRYPTTHREAD_H
#define ENCRYPTTHREAD_H

#include "tinyaes.h"
#include "setup.h"
#include "logthread.h"

#include <QThread>
#include <QString>
#include <QtCore>
#include <QProgressBar>
#include <QMutex>

class EncryptThread : public QThread
{
    Q_OBJECT

public:
    explicit EncryptThread(QObject *parent = 0);
    ~EncryptThread();
    void init(QString filePath, QByteArray key, bool cryptFlag);
    bool stop;

protected:
    void run();
    void encrypt();
    void decrypt();

private:
    TinyAES crypto;
    QString filePath;
    QByteArray key;
    bool cryptFlag;

signals:
    void sinalUpdate(int);

private slots:
    void cancelThread();
};

#endif // ENCRYPTTHREAD_H
