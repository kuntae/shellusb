#include "loadingdialog.h"
#include "ui_loadingdialog.h"

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::LoadingDialog),
    sysdir("./shell/sys/"),shellusb("shellusb.bin"),shellpiece("shellpiecce.bin")
{
    ui->setupUi(this);

    ui->label->setPixmap(QPixmap(this->sysdir + "ShellUSB.png"));
    this->setWindowFlags(Qt::FramelessWindowHint);


    SetUp::enc_url = "hi";
    qDebug() << SetUp::enc_url <<endl;

    connect(&time,SIGNAL(timeout()),this, SLOT(close()));

    this->chkSysDirectory();
    this->chkShellusbFile();
    this->chkShellpieceFile();
    time.start(1500);
}

LoadingDialog::~LoadingDialog()
{
    qDebug() << "close Loading Dialog";
    delete ui;
}

void LoadingDialog::setLogFileName(){
        QDate date = QDate::currentDate();
        QString tmpdate = QString("%1_%2_%3.log").arg(QString::number(date.year()), QString::number(date.month()), QString::number(date.day()));
        qDebug() << tmpdate<<endl;
        LogThread::logFileName = tmpdate;
}

void LoadingDialog::chkSysDirectory(){
    QDir dir;
    if(!dir.exists(this->sysdir)){
        qDebug()<<"make sysdir.";
        dir.mkpath(this->sysdir);
    }
}

void LoadingDialog::chkShellusbFile(){
    QFile file;
    file.setFileName(this->sysdir + this->shellusb);
    //check exists file.
    if(!file.exists()){
        SettingDialog settingDialog;
        settingDialog.setModal(true);
        settingDialog.exec();
    }
    QString line;
    QTextStream in( &file );
    while (!in.atEnd()){
        line = in.readLine();
        qDebug() << line;
    }

    file.close();
}

void LoadingDialog::chkShellpieceFile(){

}
