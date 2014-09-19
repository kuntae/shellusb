#include "mainwindow.h"
#include "ui_mainwindow.h"

int MainWindow::failCnt;

/**
 * @brief 생성자
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->hide();
    LoadingDialog load;
    load.setModal(true);
    load.exec();

    this->setWindowTitle("ShellUSB");
    ui->setupUi(this);
    ui->password->setText("1234");
    inText = getString(6);
    failCnt = 0;

    //보안문자 숨기기.
    ui->label->setVisible(false);
    ui->label->hide();
    ui->lineEdit->hide();
    ui->pushButton_2->hide();
    ui->pushButton->setGeometry(110, 75, 81, 23);
    this->setFixedSize(287, 121);

    // dark fusion 테마.
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
 * @brief 로그인 버튼 클릭 시 이벤트 처리 함수
 */
void MainWindow::on_pushButton_clicked()
{
    QString passWord;

    passWord = ui->password->text();

    // 패스워드가 맞은 경우.
    if (!passWord.compare(SetUp::pwd))
    {
        // Catcha가 틀린 경우.
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
    // 패스워드가 틀린 경우.
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
            ui->pushButton->setGeometry(110, 180, 81, 23);
            this->setFixedSize(287, 237);
        }
        LogThread *log = new LogThread("WARNING//Password Fail.",this);
        connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
        log->start();
    }
}

/**
 * @brief Refresh 버튼 클릭 시 이벤트 처리 함수
 */
void MainWindow::on_pushButton_2_clicked()
{
    inText = getString(6);
    distortImg(makeImg(inText));
}
