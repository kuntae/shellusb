#ifndef FILECONTROL_H
#define FILECONTROL_H

#include <QString>
#include <QFile>
#include <QDebug>
#include <QInputDialog>
#include <QDialog>

#include "tinyaes.h"
#include "progdialog.h"

class FileControl:public QFile
{
public:
    explicit FileControl(QString name);
    ~FileControl();
    void file2enc();
    void file2dec();
private:
    QString fname; //read || write file of name.
    TinyAES crypto;
    progdialog* pd;
};

#endif // FILECONTROL_H
