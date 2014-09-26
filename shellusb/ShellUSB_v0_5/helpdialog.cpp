#include "helpdialog.h"
#include "ui_helpdialog.h"

helpDialog::helpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpDialog)
{

    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(":/img/ablesoft.png"));
    this->setWindowTitle("ShellUSB");
}

helpDialog::~helpDialog()
{
    delete ui;
}
