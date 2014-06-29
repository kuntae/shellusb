#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tinyaes.h"
#include "shellusb.h"

#include <QFile>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->password->setText("1234");

    this->setWindowTitle("ShellUSB");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    TinyAES crypto;
    QString passWord;
    QByteArray key = crypto.HexStringToByte("1234");

    passWord = ui->password->text();

    QFile file("C:/Users/Simong/Desktop/v0_5/ShellUSB_v0_5/password.ShellUSB");

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

    if (!passWord.compare(inputPwd))
    {
        this->hide();

        ShellUSB shell;
        shell.setModal(true);
        shell.exec();
    }
    else
        ui->password->setText("");
}
