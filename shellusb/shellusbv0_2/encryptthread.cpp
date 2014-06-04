#include "encryptthread.h"
#include <QDebug>
/**
 * @brief EncryptThread::EncryptThread
 * @param _path -> filename
 */
EncryptThread::EncryptThread(QString _path, bool _flag):
    target(_path),cryptFlag(_flag)
{

}

EncryptThread::~EncryptThread(){
    delete fileCt;

    qDebug()<<"Thread die.";
}

void EncryptThread::run(){

    fileCt = new FileControl(this->target);

    if (this->cryptFlag)
    {

        fileCt->file2enc();
        //pd->show();
    }
    else
    {
        fileCt->file2dec();
        //pd->show();
    }
}
