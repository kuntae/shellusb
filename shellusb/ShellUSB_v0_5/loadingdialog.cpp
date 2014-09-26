#include "loadingdialog.h"
#include "ui_loadingdialog.h"

/**
 * @brief LoadingDialog의 생성자
 */
LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::LoadingDialog),
    // const 변수들의 초기화
    sysdir("./shell/sys/"),shellusb("shellusb.bin"),shellpiece("shellpiece.bin"),
    sysdirenc("./shell/enc/"),sysdirdec("./shell/dec/")
{
    ui->setupUi(this);

    // 프로그램 로고 출력
    ui->label->setPixmap(QPixmap(":/img/ShellUSB.png"));
    this->setWindowFlags(Qt::FramelessWindowHint);

    // 순간적으로 로고가 출력되는 현상을 방지하기 위한 sleep
    connect(&time,SIGNAL(timeout()),this, SLOT(close()));

    // 기본 sys 디렉토리의 유무확인
    ui->text_label->setText("check system diretory...");
    this->chkSysDirectory();

    // 설정 파일의 유무 확인
    ui->text_label->setText("check system file...");
    this->chkShellusbFile();

    // 비밀번호 파일의 유무 확인
    this->chkShellpieceFile();

    // 기본 sys 디렉토리에 log 폴더를 생성하고, enc, dec 디렉토리 생성
    ui->text_label->setText("check system diretory...");
    this->chkSysDirectory();

    // 로그를 사용하는지 확인. 사용한다면 로그파일의 이름을 설정
    if (SetUp::logFlag)
    {
        ui->text_label->setText("check log file...");
        this->setLogFileName();

        // 로그 파일이 저장된 디렉토리의 용량을 체크
        this->chkLogPeriod();
    }
    ui->text_label->setText("Welcome to ShellUSB...");

    // 1.5초 카운터를 시작
    time.start(1500);
}

LoadingDialog::~LoadingDialog()
{
    delete ui;
}
/**
 * @brief 로그파일의 이름을 설정하는 함수. 그날의 날짜로 설정 [yy_mm_dd.log]
 */
void LoadingDialog::setLogFileName()
{
        QDate date = QDate::currentDate();
        QString tmpdate = QString("%1_%2_%3.log").arg(QString::number(date.year()), QString::number(date.month()), QString::number(date.day()));
        LogThread::logFileName = sysdir +"log/" + tmpdate;
}
/**
 * @brief 디렉토리의 유무를 확인하고 없다면 생성
 */
void LoadingDialog::chkSysDirectory()
{
    QDir dir;

    if (!dir.exists(this->sysdir))
    {
        dir.mkpath(this->sysdir+"log/");
        dir.mkpath(this->sysdir + "list/");
    }

    if (!dir.exists(this->sysdirenc) && !SetUp::encUrl.isEmpty())
    {
        dir.mkpath(SetUp::encUrl);
    }

    if (!dir.exists(this->sysdirdec) && !SetUp::decUrl.isEmpty())
    {
        dir.mkpath(SetUp::decUrl);
    }
}
/**
 * @brief 설정파일의 유무를 확인하는 함수. 설정파일이 없으면 SettingDialog를 호출
 */
void LoadingDialog::chkShellusbFile()
{
    QFile file;
    file.setFileName(this->sysdir + this->shellusb);
    file.open(QFile::ReadOnly);

    // 설정파일의 유무 확인
    while (!file.exists())
    {
        SettingDialog settingDialog;
        settingDialog.setModal(true);
        settingDialog.exec();

    }

    // file이 존재하지 않는다면 파일을 생성 후 다시 open
    file.open(QFile::ReadOnly);
    QString key;
    QString value;
    QString line;
    QTextStream in(&file);

    // 파일의 내용을 한줄씩 읽고 ':'를 기준으로 왼쪽을 key, 오른쪽을 value로 저장하는 알고리즘
    while (!in.atEnd())
    {
        key.clear();
        value.clear();
        line = in.readLine();

        if (line.at(0) == '#')
            continue;

        iter = line.begin();

        for (iter; iter != line.end(); iter++)
        {
            if (*iter == ':')
            {
                iter++;
                break;
            }

            key.append(*iter);
        }

        for (iter; iter != line.end(); iter++)
        {
            value.append(*iter);
        }

        // key의 값을 비교하여 해당되는 value를 SetUp 클래스의 정적변수에 저장
        if(key == "enc") SetUp::encUrl = value;
        else if(key == "dec") SetUp::decUrl = value;
        else if(key == "bit") SetUp::bit = value.toInt();
        else if(key == "autopwd") SetUp::autopwd = value.toInt();
        else if(key == "flag") SetUp::logFlag = value.toInt();
        else if(key == "period") SetUp::period = value.toInt();
    }

    file.close();
}
/**
 * @brief 비밀번호 파일의 유무를 확인. 없다면 SettingDialog를 호출. 있다면 복호화하여 SetUp 클래스의 정적변수 pwd에 저장
 */
void LoadingDialog::chkShellpieceFile()
{
    TinyAES crypto;
    // QString를 QByteArray로 변환
    QByteArray datakey = crypto.HexStringToByte("1234");
    QFile file;
    file.setFileName(this->sysdir + this->shellpiece);
    file.open(QFile::ReadOnly);

    // 파일의 존재를 확인
    while (!file.exists())
    {
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
}

/**
 * @brief 로그파일이 저장된 디렉토리를 확인하고 초기 설정한 용량을 넘는다면 알림을 주고 삭제 여부를 확인
 * 
 */
void LoadingDialog::chkLogPeriod()
{
    QMessageBox::StandardButton btn;
    qint64 size = 0;
    QDir dir(this->sysdir+"log");

    // 알림 사용유무 확인
    if (dir.exists() && SetUp::period != 0)
    {
        size = getsize(dir.path());

        // 용량 계산
        if (size >= SetUp::period * 1024 * 1024)
        {
            btn = QMessageBox::question(this, "Information","Log file is overflow "+
                                        QString::number(SetUp::period) + " MB.\n delete?",
                                        QMessageBox::Yes|QMessageBox::No);
            if (btn == QMessageBox::Yes)
            {
                removeDirectory(this->sysdir + "log");
            }
        }
    }

    if (!dir.exists())
        dir.mkdir("../log");
}

// 디렉토리의 내용을 지우는 재귀 함수
void LoadingDialog::removeDirectory(const QString& src)
{
    QDir dir(src);
    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); i++)
    {
        QFileInfo info = list.at(i);
        QString filepath = info.filePath();

        if (info.isDir())
        {
            if (info.fileName() != ".." && info.fileName() != ".")
            {
                removeDirectory(filepath);
            }
        }
        else
        {
            QFile file;
            file.setFileName(filepath);
            file.remove();
        }
    }

    dir.rmdir(".");
}

// 디렉토리 안에 있는 내용들의 전체 사이즈를 구해오는 재귀 함수
qint64 LoadingDialog::getsize(const QString& src)
{
    QDir dir(src);
    QFileInfoList list = dir.entryInfoList();
    qint64 size = 0;

    for (int i = 0; i < list.size(); i++)
    {
        QFileInfo info = list.at(i);
        QString filepath = info.filePath();

        if (info.isDir())
        {
            if (info.fileName() != ".." && info.fileName() != ".")
            {
                 size += getsize(filepath);
            }
        }
        else
        {
            size += info.size();
        }
    }

    return size;
}
