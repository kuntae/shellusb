#ifndef ENCRYPTTHREAD_H
#define ENCRYPTTHREAD_H

#include <QThread>
#include <QString>

#include "filecontrol.h"

class EncryptThread:public QThread
{
public:
    explicit EncryptThread(QString _path, bool _flag);
    ~EncryptThread();
    void run();
private:
    FileControl* fileCt;
    QString target;
    bool cryptFlag;
};

#endif // ENCRYPTTHREAD_H
