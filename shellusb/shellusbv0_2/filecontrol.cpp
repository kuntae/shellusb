
#include "filecontrol.h"
#include <QDebug>

FileControl::FileControl(QString _name):fname(_name), pd(new progdialog)
{

}
FileControl::~FileControl(){
    delete pd;
}

void FileControl::file2enc()
{
    bool ok;

    this->setFileName(this->fname);

    QByteArray key = crypto.HexStringToByte
            (QInputDialog::getText(NULL, "key", "Enter a key", QLineEdit::Password, NULL, &ok));
    if(ok)
        pd->show();
    else
    {
        qDebug()<<"cancel.";
        return;
    }

    if (!this->open(this->ReadOnly))
    {
         qDebug() << "Could not open read file";
         return;
    }


    QByteArray data = this->readAll();

    this->close();
    this->remove();

    this->setFileName(this->fname + ".shellUSB");

    if (!this->open(this->WriteOnly))
    {
        qDebug() << "Could not open write file";
        return;
    }


    QByteArray encrypted = crypto.Encrypt(data, key);


    this->write(encrypted);


    this->flush();
    this->close();
}

void FileControl::file2dec()
{
    bool ok;

    this->setFileName(this->fname);

    QByteArray key = crypto.HexStringToByte
            (QInputDialog::getText(NULL, "key", "Enter a key", QLineEdit::Password, NULL, &ok));
    if(ok)
        pd->show();
    else
    {
        qDebug()<<"cancel.";
        return;
    }

    if (!this->open(this->ReadOnly))
    {
        qDebug() << "Could not open read file";
        return;
    }

    QByteArray data = this->readAll();

    this->close();
    this->remove();

    int firstdot = this->fname.indexOf(":");
    int lastdot = this->fname.lastIndexOf(".");
    QString filename = this->fname.mid(firstdot - 1, lastdot + 1);

    this->setFileName(filename);

    if (!this->open(this->WriteOnly))
    {
        qDebug() << "Could not open write file";
        return;
    }

    QByteArray decrypted = crypto.Decrypt(data, key);

    this->write(decrypted);

    this->flush();
    this->close();

}
