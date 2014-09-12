#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tinyaes.h"
#include "shellusb.h"

#include <QFile>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    QDate date = QDate::currentDate();
    QString tmpdate = QString("%1_%2_%3.log").arg(QString::number(date.year()), QString::number(date.month()), QString::number(date.day()));
    qDebug() << tmpdate<<endl;
    LogThread::logFileName = tmpdate;

    this->setWindowTitle("ShellUSB");
    ui->setupUi(this);
    ui->password->setText("1234");
    inText = getString(6);
    failCnt = 0;

    //보안문자 숨기기
    ui->label->setVisible(false);
    ui->label->hide();
    ui->lineEdit->hide();
    ui->pushButton_2->hide();
    ui->pushButton->setGeometry(110, 50, 81, 23);
    this->setFixedSize(287, 121);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief 랜덤하게 스트링을 생성
 * @param length
 * @return
 */
QString MainWindow::getString(int length){
    QString alphanum =
            ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    QString result;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    for(int i=0; i<length; ++i)
    {
        int index = qrand() % alphanum.length();
        QChar nextChar = alphanum.at(index);
        result.append(nextChar);
    }
    return result;
}

/**
 * @brief 텍스트를 이미지로 변환
 * @param inText
 * @return
 */
QPixmap MainWindow::makeImg(QString inText){
    QPixmap pixmap(300,150);
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",45));
    painter.drawText(15,90,inText);

    //ui->label->setPixmap(pixmap);
    return pixmap;
}

/**
 * @brief 이미지를 왜곡된 이미지로 변환
 * @param pixmap
 * @return
 */
void MainWindow::distortImg(QPixmap pixmap)
{
    QImage pixmapImg = pixmap.toImage();
    QPixmap pixmap2(pixmap.width(),pixmap.height());
    QPainter painter2(&pixmap2);

    // Distort text
    for(int x = 0; x < pixmap.width(); x++){
        for(int y = 0; y < pixmap.height(); y++){
            qsrand(x);
            float rand1 = qrand()%5;
            qsrand(y);
            float rand2 = qrand()%5;
            float sinx = sin((float)x/10+1)*5;
            float siny = qSin((float)y/10)*5;
            int newx = x+rand1+sinx;
            int newy = y+rand2+siny;
            if(newx < pixmap.width() && newy < pixmap.height()){
                if(rand1+rand2 > 1) {
                    painter2.setPen(pixmapImg.pixel(newx,newy));
                } else {
                    painter2.setPen(Qt::black);
                    painter2.drawRect(x,y,10,10);
                }
                painter2.drawRect(x,y,1,1);

            }
        }
    }
    ui->label->setPixmap(pixmap2);
}

/**
 * @brief 로그인 버튼 클릭
 */
void MainWindow::on_pushButton_clicked()
{
    TinyAES crypto;
    QString passWord;
    QByteArray key = crypto.HexStringToByte("1234");

    passWord = ui->password->text();

    QFile file("../ShellUSB_v0_5/password.ShellUSB");
    // open a password file
    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "Could not open read file";
        return;
    }

    QByteArray data = file.readAll();

    file.close();

    QByteArray input = crypto.Decrypt(data, key);
    QString inputPwd(input);

    // 패스워드가 맞은 경우
    if (!passWord.compare(inputPwd))
    {
        // Catcha가 틀린 경우
        if(failCnt >= 3 && QString::compare(inText, ui->lineEdit->text()) != 0) {
            //ui->label_2->setText("They are different.");
            inText = getString(6);
            distortImg(makeImg(inText));
            ui->password->setText("");
            ui->label_2->setText("Catcha Fail ");
            return;
        }
        this->hide();
        LogThread *log = new LogThread("PASSED//Program start.",this);
        connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
        log->start();
        ShellUSB shell;
        shell.setModal(true);
        shell.exec();
    }
    // 패스워드가 틀린 경우
    else {
        ui->label_2->setText("Password Fail ");
        ui->password->setText("");
        failCnt++;

        if(failCnt >= 3) {
            inText = getString(6);
            distortImg(makeImg(inText));
            ui->label->setVisible(true);
            ui->label->show();
            ui->lineEdit->show();
            ui->pushButton_2->show();
            ui->pushButton->setGeometry(110, 150, 81, 23);
            this->setFixedSize(287, 257);
        }
        LogThread *log = new LogThread("WARNING//Password Fail.",this);
        connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
        log->start();
    }
}

/**
 * @brief Refresh 버튼 클릭
 */
void MainWindow::on_pushButton_2_clicked()
{
    inText = getString(6);
    distortImg(makeImg(inText));
}
