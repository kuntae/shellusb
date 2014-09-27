#include "progdialog.h"
#include "ui_progdialog.h"

ProgDialog::ProgDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgDialog)
{
    ui->setupUi(this);
    qDebug() << "dialog created";
}
void ProgDialog::init(QString filePath, QByteArray key, bool cryptFlag)
{
    //qDebug() << "dialog: " << filePath << " " << key << " " << cryptFlag;

    int lastSlash = filePath.lastIndexOf("/");
    filename = filePath.mid(lastSlash + 1);

    if (cryptFlag)
        this->setWindowTitle("<Encrypting> " + filename);
    else
        this->setWindowTitle("<Decrypting> " + filename);

    // 암복호화 쓰레드 생성
    encryptThread = new EncryptThread(this);
    encryptThread->init(filePath, key, cryptFlag);

    // 암복호화 완료 시 encryptThread, prodDialog 소멸
    connect(encryptThread, SIGNAL(finished()), encryptThread, SLOT(deleteLater()));
    connect(encryptThread, SIGNAL(finished()), this, SLOT(deleteLater()));

    // 암복호화 진행상태를 표시
    connect(encryptThread, SIGNAL(sinalUpdate(int)), this, SLOT(updatePd(int)));

    // 암복호화 쓰레드 시작
    encryptThread->start();
}

ProgDialog::~ProgDialog()
{
    qDebug() << "dialog die";
    delete ui;
}

void ProgDialog::updatePd(int i)
{
    ui->progressBar->setValue(i);
}

void ProgDialog::on_cancel_clicked()
{
    // QMutex를 사용해 쓰레드를 종료
    encryptThread->stop = true;

    if (SetUp::logFlag)
    {
        LogThread *log = new LogThread("CANCELED//Encryption or Decryption file: [ " + this->filename + " ]",this);
        connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
        log->start();
    }
}
