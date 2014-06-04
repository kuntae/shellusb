#include "shellusb.h"
#include "ui_shellusb.h"

shellusb::shellusb(QWidget *parent) :
    QDialog(parent), ui(new Ui::shellusb), model(new QFileSystemModel(this)),lt(new std::list<QString>),iter(lt->rbegin())
{
    ui->setupUi(this);

    ui->front_btn->setDisabled(true); //if listFront !=NULL then front_btn enable else then front_btn disabled.
    ui->back_btn->setDisabled(true);

    model->setReadOnly(true);
    ui->tableView->setModel(model);

    ui->tableView->setRootIndex(model->setRootPath("../shellusbv0_2/"));

    ui->back_btn->setIcon(QIcon("../shellusbv0_2/back.png"));
    ui->front_btn->setIcon(QIcon("../shellusbv0_2/front.png"));
    ui->help_btn->setIcon(QIcon("../shellusbv0_2/help.png"));

}

shellusb::~shellusb()
{
    delete ui;
}

void shellusb::on_enc_btn_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    EncryptThread(model->fileInfo(index).absoluteFilePath(), true).run();
}

void shellusb::on_dnc_btn_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    EncryptThread(model->fileInfo(index).absoluteFilePath(), false).run();
}

void shellusb::on_back_btn_clicked()
{
    ui->front_btn->setDisabled(false);
    ui->tableView->setRootIndex(model->setRootPath(*iter+"/.."));
    if(iter != lt->rend())
        iter++;
    if(iter == lt->rend())
        ui->back_btn->setDisabled(true);
}

void shellusb::on_front_btn_clicked()
{
    ui->back_btn->setDisabled(false);
    if(iter != lt->rbegin())
    {
        iter--;
        ui->tableView->setRootIndex(model->setRootPath(*iter));
    }
    if(iter == lt->rbegin())
        ui->front_btn->setDisabled(true);
}

void shellusb::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(model->fileInfo(index).isDir()){
        ui->tableView->setRootIndex(model->setRootPath(model->fileInfo(index).absoluteFilePath()));
        lt->push_back(model->fileInfo(index).absoluteFilePath());
        ui->back_btn->setDisabled(false);
    }
    else
    {
        QDesktopServices* ds = new QDesktopServices;
        ds->openUrl(QUrl(model->fileInfo(index).absoluteFilePath()));
    }
}
