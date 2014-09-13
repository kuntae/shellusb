#include "loadingdialog.h"
#include "ui_loadingdialog.h"

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::LoadingDialog),
    sysdir("./shell/sys/"),shellusb("shellusb.bin"),shellpiece("shellpiece.bin")
{
    ui->setupUi(this);

    ui->label->setPixmap(QPixmap(this->sysdir + "ShellUSB.png"));
    this->setWindowFlags(Qt::FramelessWindowHint);

    connect(&time,SIGNAL(timeout()),this, SLOT(close()));

    ui->text_label->setText("check system diretory...");
    this->chkSysDirectory();
    ui->text_label->setText("check system file...");
    this->chkShellusbFile();
    this->chkShellpieceFile();

    if(SetUp::logFlag){
        ui->text_label->setText("check log file...");
        this->setLogFileName();
        this->chkLogPeriod();
    }
    ui->text_label->setText("Welcome to ShellUSB...");
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
    file.open(QFile::ReadOnly);
    //check exists file.
    if(!file.exists()){
        SettingDialog settingDialog;
        settingDialog.setModal(true);
        settingDialog.exec();
    }
    QString key;
    QString value;
    QString line;
    QTextStream in( &file );
    while (!in.atEnd()){
        key.clear();
        value.clear();
        line = in.readLine();
        if(line.at(0) == '#') continue;

        iter = line.begin();
        for(iter; iter != line.end(); iter++){
            if(*iter == ':'){
                iter++;
                break;
            }
            key.append(*iter);
        }

        for(iter; iter != line.end(); iter++){
            value.append(*iter);
        }


        if(key == "enc") SetUp::encUrl = value;
        else if(key == "dec") SetUp::decUrl = value;
        else if(key == "byte") SetUp::byte = value.toInt();
        else if(key == "lang") SetUp::lang = value;
        else if(key == "flag") SetUp::logFlag = value.toInt();
        else if(key == "period") SetUp::period = value.toInt();

    }
    file.close();
}

void LoadingDialog::chkShellpieceFile(){
    TinyAES crypto;
    QByteArray datakey = crypto.HexStringToByte("1234");
    QFile file;
    file.setFileName(this->sysdir + this->shellpiece);
    file.open(QFile::ReadOnly);

    QByteArray data = file.readAll();
    file.close();

    QByteArray decData = crypto.Decrypt(data,datakey);
    SetUp::pwd = QString(decData);

    qDebug()<<"(" << SetUp::pwd <<")";
}

void LoadingDialog::chkLogPeriod(){
    qDebug() << "call chkLogPeriod";
}
