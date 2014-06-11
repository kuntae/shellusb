#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tinyaes.h"
#include "shellusb.h"

#include <QFile>
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    TinyAES crypto;
    QString password;
    QByteArray key = crypto.HexStringToByte("1234");

    password = ui->password->text();

    QFile file("../shellusbv0_2/password.txt.shellUSB");

    if(!file.open(QFile::ReadOnly)) {
        qDebug() << "Could not open read file";
        return;
    }

    QByteArray data = file.readAll();

    file.close();

    QByteArray input = crypto.Decrypt(data, key);
    QString inputpwd(input);

    if(!password.compare(inputpwd)) {
        this->hide();
        shellusb shell;
        shell.setModal(true);
        shell.exec();
    }
    else{
        QMessageBox::warning(NULL,"Warning","비밀번호가 일치하지 않습니다.");
        ui->password->setText("");
    }
}
