#include "helpdialog.h"
#include "ui_helpdialog.h"

//helpDialog는 팀 로고와 제작자의 이름, 이메일을 보여주기 위한 Dialog임.
helpDialog::helpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpDialog)
{
    ui->setupUi(this);

    //label에 이미지 출력.
    ui->label->setPixmap(QPixmap(":/img/ablesoft.png"));
    this->setWindowTitle("ShellUSB");
}

helpDialog::~helpDialog()
{
    delete ui;
}
