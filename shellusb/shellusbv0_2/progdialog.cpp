#include "progdialog.h"
#include "ui_progdialog.h"

progdialog::progdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::progdialog)
{
    ui->setupUi(this);
}

progdialog::~progdialog()
{
    delete ui;
}

void progdialog::on_pushButton_clicked()
{

}

void progdialog::onChangeNumber(int i) {
    ui->progressBar->setValue(i);
}
