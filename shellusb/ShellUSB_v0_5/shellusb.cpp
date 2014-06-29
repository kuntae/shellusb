#include "shellusb.h"
#include "ui_shellusb.h"

ShellUSB::ShellUSB(QWidget *parent) :
    QDialog(parent), ui(new Ui::ShellUSB), model(new QFileSystemModel(this)), lt(new std::list<QString>), iter(lt->rbegin())
{
    ui->setupUi(this);

    this->setWindowTitle("ShellUSB");

    // 맨처음 경로 저
    lt->push_back(model->rootPath());

    ui->front_btn->setDisabled(true); //if listFront !=NULL then front_btn enable else then front_btn disabled.
    ui->back_btn->setDisabled(true);

    model->setReadOnly(true);

    ui->tableView->setModel(model);
    ui->tableView->setRootIndex(model->setRootPath("C:/Users/Simong/Desktop"));

    // set icon images
    ui->back_btn->setIcon(QIcon("../ShellUSB_v0_5/back.png"));
    ui->front_btn->setIcon(QIcon("../ShellUSB_v0_5/front.png"));
    ui->help_btn->setIcon(QIcon("../ShellUSB_v0_5/help.png"));

    // drag and drop part
    ui->tableView->setAcceptDrops(true);
    ui->tableView->setDragEnabled(true);
    ui->tableView->setDropIndicatorShown(true);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setDefaultDropAction(Qt::MoveAction);
    ui->tableView->setDragDropMode(QAbstractItemView::DragDrop);

    treeModel = new QDirModel(this);

    // 폴더나 파일을 추가, 삭제 불가능하도록 설정
    treeModel->setReadOnly(true);

    // 정렬
    treeModel->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name );

    // treeView에 프로그램이 실행된 Root 디렉토리를 표시
    QModelIndex index = treeModel->index(QDir::rootPath());
    ui->treeView->setModel(treeModel);
    ui->treeView->setRootIndex(index);
    ui->treeView->setCurrentIndex(index);

    // treeView 이쁘게
    ui->treeView->expand(index);
    ui->treeView->scrollTo(index);
    ui->treeView->resizeColumnToContents(0);
}

ShellUSB::~ShellUSB()
{
    delete ui;
}

void ShellUSB::on_enc_btn_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();

    // extract a file extension
    int lastDot = model->fileInfo(index).absoluteFilePath().lastIndexOf(".");
    QString duplicated = model->fileInfo(index).absoluteFilePath().mid(lastDot, 9);

    // inspect whether file name is duplicated
    if (!duplicated.compare(".ShellUSB"))
    {
        QMessageBox::warning(NULL, "Warning", "This file is already encrypted");
        qDebug() << "duplicated";

        return;
    }

    // input a key
    QByteArray key = crypto.HexStringToByte
            (QInputDialog::getText(NULL, "key", "Enter a key", QLineEdit::Password, NULL, &ok));

    if (!ok)
    {
        qDebug() << "canceled";
        return;
    }

    // ProgDialog 생성
    ProgDialog *progDialog = new ProgDialog(this);
    progDialog->init(model->fileInfo(index).absoluteFilePath(), key, true);
    progDialog->show();
}

void ShellUSB::on_dnc_btn_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();

    // extract a file extension
    int lastDot = model->fileInfo(index).absoluteFilePath().lastIndexOf(".");
    QString duplicated = model->fileInfo(index).absoluteFilePath().mid(lastDot, 9);

    // inspect whether file name is duplicated
    if (duplicated.compare(".ShellUSB"))
    {
        QMessageBox::warning(NULL, "Warning", "This file is not encrypted");
        qDebug() << "duplicated";

        return;
    }

    // input a key
    QByteArray key = crypto.HexStringToByte
            (QInputDialog::getText(NULL, "key", "Enter a key", QLineEdit::Password, NULL, &ok));

    if (!ok)
    {
        qDebug() << "canceled";
        return;
    }

    // ProgDialog 생성
    ProgDialog *progDialog = new ProgDialog(this);
    progDialog->init(model->fileInfo(index).absoluteFilePath(), key, false);
    progDialog->show();
}

void ShellUSB::on_back_btn_clicked()
{
    // 뒤로 이동
    iter++;
    ui->tableView->setRootIndex(model->setRootPath(*iter));

    // front 버튼 활성화
    ui->front_btn->setDisabled(false);

    // 리스트의 맨 앞인 경우 back버튼 비활성화
    if (iter == --lt->rend())
        ui->back_btn->setDisabled(true);
}

void ShellUSB::on_front_btn_clicked()
{
    // 앞으로 이동
    iter--;
    ui->tableView->setRootIndex(model->setRootPath(*iter));

    // back버튼 활성화
    ui->back_btn->setDisabled(false);

    // 리스트의 맨 뒤인 경우 front버튼 비활성화
    if (iter == lt->rbegin())
        ui->front_btn->setDisabled(true);
}

void ShellUSB::on_tableView_doubleClicked(const QModelIndex &index)
{
    // 디렉토리를 더블클릭한 경우
    if (model->fileInfo(index).isDir())
    {
        // iter 뒤에 있는 lt의 노드들을 삭제한다.
        int tmp = 0;
        std::list<QString>::reverse_iterator it = lt->rbegin();

        while (it != lt->rend())
        {
            if(it == iter)
                break;
            else
                tmp++;
            it++;
        }
        for (int i = 0; i < tmp; i++)
            lt->pop_back();

        // lt 뒤에 새로운 위치 add
        lt->push_back(model->fileInfo(index).absoluteFilePath());

        // 더블클릭한 위치로 이동
        ui->tableView->setRootIndex(model->setRootPath(model->fileInfo(index).absoluteFilePath()));

        // back버튼 활성화/ front버튼 비활성화
        ui->back_btn->setDisabled(false);
        ui->front_btn->setDisabled(true);
    }
    // 파일을 더블클릭한 경우
    else
    {
        QDesktopServices* ds = new QDesktopServices;
        ds->openUrl(QUrl(model->fileInfo(index).absoluteFilePath()));
    }
}

void ShellUSB::on_treeView_clicked(const QModelIndex &treeIndex)
{
    // 선택된 파일 or 디렉토리 경로
    QString path = treeModel->filePath(treeIndex);
    QFileInfo pathInfo(path);

    // 디렉토리 일 경우
    if (pathInfo.isDir())
    {
        // iter뒤에 있는 lt의 노드들을 삭제한다.
        int tmp = 0;
        std::list<QString>::reverse_iterator it = lt->rbegin();

        while (it != lt->rend())
        {
            if (it == iter)
                break;
            else
                tmp++;
            it++;
        }

        for (int i = 0; i < tmp; i++)
        {
            lt->pop_back();
        }

        // lt 뒤에 새로운 위치 add
        QString newPath = treeModel->filePath(treeIndex);
        lt->push_back(newPath);
        iter = lt->rbegin();

        // treeView에서 선택한 위치로 tableView 이동
        ui->tableView->setRootIndex(model->setRootPath(path));

        // back버튼 활성화/ front버튼 비활성화
        ui->back_btn->setDisabled(false);
        ui->front_btn->setDisabled(true);
    }
}
