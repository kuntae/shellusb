#include "loadingdialog.h"
#include "ui_loadingdialog.h"


LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::LoadingDialog),
    sysdir("./shell/sys/"),shellusb("shellusb.bin"),shellpiece("shellpiece.bin"),
    sysdirenc("./shell/enc/"),sysdirdec("./shell/dec/")
{
    ui->setupUi(this);

    ui->label->setPixmap(QPixmap(":/img/ShellUSB.png"));
    this->setWindowFlags(Qt::FramelessWindowHint);

    // program logo default print time set.
    connect(&time,SIGNAL(timeout()),this, SLOT(close()));

    ui->text_label->setText("check system diretory...");
    this->chkSysDirectory();

    ui->text_label->setText("check system file...");
    this->chkShellusbFile();
    this->chkShellpieceFile();
    ui->text_label->setText("check system diretory...");
    this->chkSysDirectory();
    if(SetUp::logFlag){
        ui->text_label->setText("check log file...");
        this->setLogFileName();
        this->chkLogPeriod();
    }
    ui->text_label->setText("Welcome to ShellUSB...");
    //timer start. 1.5sec
    time.start(1500);
}

LoadingDialog::~LoadingDialog()
{
    qDebug() << "close Loading Dialog";
    delete ui;
}
/**
 * @brief init logfile name. "yy_mm_dd.log"
 */
void LoadingDialog::setLogFileName(){
        QDate date = QDate::currentDate();
        QString tmpdate = QString("%1_%2_%3.log").arg(QString::number(date.year()), QString::number(date.month()), QString::number(date.day()));
        qDebug() << tmpdate<<endl;
        LogThread::logFileName = sysdir +"log/" + tmpdate;
}
/**
 * @brief check shell/sys directory and make it.
 */
void LoadingDialog::chkSysDirectory(){
    QDir dir;
    if(!dir.exists(this->sysdir)){
        qDebug()<<"make sysdir.";
        dir.mkpath(this->sysdir+"log/");
    }
    if(!dir.exists(this->sysdirenc) && !SetUp::encUrl.isEmpty()){
        qDebug()<<"make sysdirenc.";
        dir.mkpath(SetUp::encUrl);
    }
    if(!dir.exists(this->sysdirdec) && !SetUp::decUrl.isEmpty()){
        qDebug()<<"make sysdirdec.";
        dir.mkpath(SetUp::decUrl);
    }
}
/**
 * @brief check system file. if don't exists, run Setting dialog.
 */
void LoadingDialog::chkShellusbFile(){
    QFile file;
    file.setFileName(this->sysdir + this->shellusb);
    file.open(QFile::ReadOnly);
    //check exists file.
    while(!file.exists()){
        SettingDialog settingDialog;
        settingDialog.setModal(true);
        settingDialog.exec();

    }
    // file이 존재하지 않는다면 파일을 생성 후 다시 open
    file.open(QFile::ReadOnly);
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
        else if(key == "bit") SetUp::bit = value.toInt();
        else if(key == "lang") SetUp::lang = value;
        else if(key == "flag") SetUp::logFlag = value.toInt();
        else if(key == "period") SetUp::period = value.toInt();
    }
    file.close();
}
/**
 * @brief read and decrypt password file.
 */
void LoadingDialog::chkShellpieceFile(){
    TinyAES crypto;
    QByteArray datakey = crypto.HexStringToByte("1234");
    QFile file;
    file.setFileName(this->sysdir + this->shellpiece);
    file.open(QFile::ReadOnly);
    //check exists file.
    while(!file.exists()){
        SettingDialog settingDialog;
        settingDialog.setModal(true);
        settingDialog.exec();

    }
    // file이 존재하지 않는다면 파일을 생성 후 다시 open
    file.open(QFile::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    QByteArray decData = crypto.Decrypt(data,datakey);
    SetUp::pwd = QString(decData);

    qDebug()<<"(" << SetUp::pwd <<")";
}

/**
 * @brief check log file. if log file name is delete name than delete file.
 * 
 */
void LoadingDialog::chkLogPeriod(){
    QMessageBox::StandardButton btn;
    qint64 size = 0;
    QDir dir(this->sysdir+"log");
    qDebug() <<"#"+dir.path();
    if(dir.exists() && SetUp::period != 0){
        size = getsize(dir.path());
        if(size >= SetUp::period * 1024 * 1024){
            btn = QMessageBox::question(this, "Information","Log file is overflow "+
                                        QString::number(SetUp::period) + " MB.\n delete?",
                                        QMessageBox::Yes|QMessageBox::No);
            if(btn == QMessageBox::Yes){
                removeDirectory(this->sysdir + "log");
            }
        }
    }
    if(!dir.exists()) dir.mkdir("../log");
}

void LoadingDialog::removeDirectory(const QString& src){
    QDir dir(src);
    QFileInfoList list = dir.entryInfoList();
    for(int i = 0; i < list.size(); i++){
        QFileInfo info = list.at(i);
        QString filepath = info.filePath();
        if(info.isDir()){
            if(info.fileName() != ".." && info.fileName() != "."){
                removeDirectory(filepath);
            }
        }else{
            QFile file;
            file.setFileName(filepath);
            file.remove();
        }
    }
    dir.rmdir(".");
}

qint64 LoadingDialog::getsize(const QString& src){
    QDir dir(src);
    QFileInfoList list = dir.entryInfoList();
    qint64 size = 0;
    for(int i = 0; i < list.size(); i++){
        QFileInfo info = list.at(i);
        QString filepath = info.filePath();
        if(info.isDir()){
            if(info.fileName() != ".." && info.fileName() != "."){
                 size += getsize(filepath);
            }
        }else{
            size += info.size();
        }
    }
    return size;
}
