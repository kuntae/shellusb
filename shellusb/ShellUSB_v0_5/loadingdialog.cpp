#include "loadingdialog.h"
#include "ui_loadingdialog.h"

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::LoadingDialog),
    sysdir("./shell/sys/"),shellusb("shellusb.bin"),shellpiece("shellpiecce.bin")
{
    ui->setupUi(this);

    ui->label->setPixmap(QPixmap(this->sysdir+"ShellUSB.png"));
    this->setWindowFlags(Qt::FramelessWindowHint);

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

void LoadingDialog::setLogFileName(QString name){
    LogThread::logFileName = name;
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
    file.setFileName(this->sysdir+"/"+this->shellusb);
    //check exists file.
    if(!file.exists()){
        SettingDialog settingDialog;
        settingDialog.setModal(true);
        settingDialog.exec();
    }

    qDebug() <<"start setup class";
    file.close();
}

void LoadingDialog::chkShellpieceFile(){

}
