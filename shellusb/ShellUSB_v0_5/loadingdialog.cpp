#include "loadingdialog.h"
#include "ui_loadingdialog.h"

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);

    ui->label->setPixmap(QPixmap("./ShellUSB.png"));
    this->setWindowFlags(Qt::FramelessWindowHint);

    connect(&time,SIGNAL(timeout()),this, SLOT(close()));
    this->setLogFileName();
    time.start(1500);
}

LoadingDialog::~LoadingDialog()
{
    qDebug() << "close Loading Dialog";
    delete ui;
}

void LoadingDialog::setLogFileName(){

}
