#include "progdialog.h"
#include "ui_progdialog.h"

/**
 * @brief 생성자
 * @param parent
 */
ProgDialog::ProgDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgDialog)
{
    ui->setupUi(this);
    qDebug() << "dialog created";

    // 1. dark fusion 테마
    qApp->setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(darkPalette);

    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
}

/**
 * @brief 암복호화 시작 전에 필요한 작업을 수행하는 함수
 * @param filePath
 * @param key
 * @param cryptFlag
 */
void ProgDialog::init(QString filePath, QByteArray key, bool cryptFlag) {
    //qDebug() << "dialog: " << filePath << " " << key << " " << cryptFlag;

    int lastSlash = filePath.lastIndexOf("/");
    QString fileName = filePath.mid(lastSlash + 1);
    if (cryptFlag)
        this->setWindowTitle("<Encrypting> " + fileName);
    else
        this->setWindowTitle("<Decrypting> " + fileName);

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

/**
 * @brief 프로그래스바를 이용해 암복호화 진행상태를 표시하는 함수
 * @param i
 */
void ProgDialog::updatePd(int i)
{
    ui->progressBar->setValue(i);
}

/**
 * @brief 암복호화 도중 사용자가 취소 버튼을 클릭 시 이벤트 처리 함수
 */
void ProgDialog::on_cancel_clicked()
{
    // QMutex를 사용해 쓰레드를 종료
    encryptThread->stop = true;
}
