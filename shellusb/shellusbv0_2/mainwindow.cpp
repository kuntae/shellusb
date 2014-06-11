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
    this->setWindowTitle("ShellUSB");
    ui->password->setText("1234");
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

    QFile file("C:/Users/Simong/Desktop/shellusbv0_2/shellusbv0_2/password.shellUSB");

    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "Could not open read file";
        return;
    }

    QByteArray data = file.readAll();

    file.close();

    QByteArray input = crypto.Decrypt(data, key);
    QString inputpwd(input);

    if (!password.compare(inputpwd))
    {
        this->hide();
        shellusb shell;
        shell.setModal(true);
        shell.exec();
    }
    else
        ui->password->setText("");
}