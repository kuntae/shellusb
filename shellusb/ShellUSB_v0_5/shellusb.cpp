#include "shellusb.h"
#include "ui_shellusb.h"

/**
 * @brief 생성자
 * @param parent
 */
ShellUSB::ShellUSB(QWidget *parent) :
    QDialog(parent), ui(new Ui::ShellUSB), model(new QFileSystemModel(this)), lt(new std::list<QString>), iter(lt->rbegin())
{
    ui->setupUi(this);

    // 1. dark fusion 테마
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

    this->setWindowTitle("ShellUSB");

    // 맨처음 경로 저장
    //model->setRootPath(SetUp::encUrl);


    // 버튼 비활성화
    ui->front_btn->setDisabled(true); //if listFront !=NULL then front_btn enable else then front_btn disabled.
    ui->back_btn->setDisabled(true);

//    model->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
//    model->setReadOnly(true);
    //model->setRootPath(SetUp::encUrl);

    //ui->tableView->setModel(model);
    qDebug() << SetUp::encUrl;


    // set icon images
    ui->back_btn->setIcon(QIcon(":/img/back.png"));
    ui->front_btn->setIcon(QIcon(":/img/front.png"));
    ui->help_btn->setIcon(QIcon(":/img/help.png"));



//    // drag and drop part
//    //ui->tableView->setRootIndex(model->setRootPath(SetUp::encUrl));
//    //ui->tableView->setCurrentIndex(index);
//    ui->tableView->setAcceptDrops(true);
//    ui->tableView->setDragEnabled(true);
//    ui->tableView->setDropIndicatorShown(true);
//    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
//    ui->tableView->setDefaultDropAction(Qt::MoveAction);
//    ui->tableView->setDragDropMode(QAbstractItemView::DragDrop);

//    // 왼쪽에 표시될 트리뷰(탐색기와 같은 효과)
//    treeModel = new QDirModel(this);
//    treeModel->setReadOnly(true);   // 폴더나 파일을 추가, 삭제 불가능하도록 설정
//    treeModel->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name );    // 정렬

//    // treeView에 프로그램이 실행된 Root 디렉토리를 표시

//    QModelIndex index = treeModel->index(SetUp::encUrl);

////    ui->treeView->setColumnHidden(1,true);
////    ui->treeView->setColumnHidden(2,true);
////    ui->treeView->setColumnHidden(3,true);
//    //ui->treeView->setRootIndex(index);
//    ui->treeView->setCurrentIndex(index);

//    // treeView 이쁘게
//    ui->treeView->expand(index);
//    ui->treeView->scrollTo(index);
//    ui->treeView->resizeColumnToContents(0);
    QModelIndex index;
    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(SetUp::encUrl);

    lt->push_back(dirModel->rootPath());

    index = dirModel->index(SetUp::encUrl);

    ui->treeView->setModel(dirModel);
    ui->treeView->setColumnHidden(1,true);
    ui->treeView->setColumnHidden(2,true);
    ui->treeView->setColumnHidden(3,true);
    ui->treeView->setCurrentIndex(index);

    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot|QDir::AllEntries);
    fileModel->setRootPath(SetUp::encUrl);

    index = fileModel->index(SetUp::encUrl);

    ui->tableView->setModel(fileModel);
    ui->tableView->setRootIndex(index);

    ui->tableView->setAcceptDrops(true);
    ui->tableView->setDragEnabled(true);
    ui->tableView->setDropIndicatorShown(true);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setDefaultDropAction(Qt::MoveAction);
    ui->tableView->setDragDropMode(QAbstractItemView::DragDrop);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

}

ShellUSB::~ShellUSB()
{
    delete ui;
}

/**
 * @brief enc 버튼 클릭 시 이벤트 처리 함수
 */
void ShellUSB::on_enc_btn_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();

    // extract a file extension
//    int lastDot = model->fileInfo(index).absoluteFilePath().lastIndexOf(".");
//    QString duplicated = model->fileInfo(index).absoluteFilePath().mid(lastDot, 9);

    int lastDot = fileModel->fileInfo(index).absoluteFilePath().lastIndexOf(".");
    QString duplicated = fileModel->fileInfo(index).absoluteFilePath().mid(lastDot, 9);

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
        if(SetUp::logFlag){
            LogThread *log = new LogThread("CANCELED//Insert password.",this);
            connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
            log->start();
        }
        return;
    }
    if(SetUp::logFlag){
        LogThread *log = new LogThread("WARNING//Encryption file: [ " + fileModel->fileInfo(index).absoluteFilePath()+ " ]",this);
        connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
        log->start();
    }
    // ProgDialog 생성
    ProgDialog *progDialog = new ProgDialog(this);
    //progDialog->init(model->fileInfo(index).absoluteFilePath(), key, true);
    progDialog->init(fileModel->fileInfo(index).absoluteFilePath(), key, true);
    progDialog->show();
}

/**
 * @brief dec 버튼 클릭 시 이벤트 처리 함수
 */
void ShellUSB::on_dnc_btn_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();

    // extract a file extension
//    int lastDot = model->fileInfo(index).absoluteFilePath().lastIndexOf(".");
//    QString duplicated = model->fileInfo(index).absoluteFilePath().mid(lastDot, 9);

    int lastDot = fileModel->fileInfo(index).absoluteFilePath().lastIndexOf(".");
    QString duplicated = fileModel->fileInfo(index).absoluteFilePath().mid(lastDot, 9);

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
        if(SetUp::logFlag){
            LogThread *log = new LogThread("CANCELED//Insert password.",this);
            connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
            log->start();
        }
        return;
    }

    if(SetUp::logFlag){
        LogThread *log = new LogThread("WARNING//Decryption file: [ " + fileModel->fileInfo(index).absoluteFilePath()+ " ]",this);
        connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
        log->start();
    }

    // ProgDialog 생성
    ProgDialog *progDialog = new ProgDialog(this);
    //progDialog->init(model->fileInfo(index).absoluteFilePath(), key, false);
    progDialog->init(fileModel->fileInfo(index).absoluteFilePath(), key, false);
    progDialog->show();
}

/**
 * @brief 뒤로 가기 버튼 클릭 시 이벤트 처리 함수
 */
void ShellUSB::on_back_btn_clicked()
{
    // 뒤로 이동
    iter++;
    //ui->tableView->setRootIndex(model->setRootPath(*iter));
    ui->tableView->setRootIndex(fileModel->setRootPath(*iter));
    ui->treeView->setCurrentIndex(dirModel->setRootPath(*iter));
    // front 버튼 활성화
    ui->front_btn->setDisabled(false);

    // 리스트의 맨 앞인 경우 back버튼 비활성화
    if (iter == --lt->rend())
        ui->back_btn->setDisabled(true);
}

/**
 * @brief 앞으로 가기 버튼 클릭 시 이벤트 처리 함수
 */
void ShellUSB::on_front_btn_clicked()
{
    // 앞으로 이동
    iter--;
    //ui->tableView->setRootIndex(model->setRootPath(*iter));
    ui->tableView->setRootIndex(fileModel->setRootPath(*iter));
    ui->treeView->setCurrentIndex(dirModel->setRootPath(*iter));
    // back버튼 활성화
    ui->back_btn->setDisabled(false);

    // 리스트의 맨 뒤인 경우 front버튼 비활성화
    if (iter == lt->rbegin())
        ui->front_btn->setDisabled(true);
}

/**
 * @brief 오른쪽의 테이블뷰을 두 번 클릭한 경우 이벤트 처리 함수
 * @param index
 */
void ShellUSB::on_tableView_doubleClicked(const QModelIndex &index)
{
    // 디렉토리를 더블클릭한 경우
    if (fileModel->fileInfo(index).isDir())
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
        //lt->push_back(model->fileInfo(index).absoluteFilePath());

        QString path = fileModel->fileInfo(index).absoluteFilePath();
        if(lt->back() != path)
            lt->push_back(path);
        // 더블클릭한 위치로 이동
        //ui->tableView->setRootIndex(model->setRootPath(model->fileInfo(index).absoluteFilePath()));
        ui->tableView->setRootIndex(fileModel->setRootPath(path));
        ui->treeView->setCurrentIndex(dirModel->setRootPath(path));

        // back버튼 활성화/ front버튼 비활성화
        ui->back_btn->setDisabled(false);
        ui->front_btn->setDisabled(true);
    }
    // 파일을 더블클릭한 경우
    else
    {
        QTextCodec * codec = QTextCodec::codecForName("utf-8");
        QString localeStr = codec->toUnicode(fileModel->fileInfo(index).absoluteFilePath().toLatin1());
        QDesktopServices* ds = new QDesktopServices();
        ds->openUrl(QUrl(localeStr));
        if(SetUp::logFlag){
            LogThread *log = new LogThread("SUCCESSED//execute file: [ " + fileModel->fileInfo(index).absoluteFilePath()+ " ]",this);
            connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
            log->start();
        }
    }
}

/**
 * @brief 왼쪽의 트리뷰를 클릭한 경우 이벤트 처리 함수
 * @param treeIndex
 */
void ShellUSB::on_treeView_clicked(const QModelIndex &treeIndex)
{
    // 선택된 파일 or 디렉토리 경로
    QString path = dirModel->filePath(treeIndex);
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
        QString newPath = dirModel->filePath(treeIndex);
        if(lt->back() != newPath){
            lt->push_back(newPath);
            iter = lt->rbegin();
        }

        // treeView에서 선택한 위치로 tableView 이동
        ui->tableView->setRootIndex(fileModel->setRootPath(path));

        // back버튼 활성화/ front버튼 비활성화
        ui->back_btn->setDisabled(false);
        ui->front_btn->setDisabled(true);
    }
}


void ShellUSB::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex idx = ui->tableView->indexAt(pos);
    QPoint globalPos = ui->tableView->viewport()->mapToGlobal(pos);

    if(fileModel->fileInfo(idx).path().compare(".") == 0) return;
    QMenu menu;
    menu.addAction("Run");
    menu.addAction("remove");

    QAction* selectedItem = menu.exec(globalPos);

    if(selectedItem){
        QString select = selectedItem->text();
        if(select.compare("Run") == 0){
            qDebug() <<"Run";
        }else if(select.compare("remove") == 0){
            qDebug() <<"remove"<<fileModel->fileInfo(idx).absoluteFilePath();
            QFile file(fileModel->fileInfo(idx).absoluteFilePath());
            file.remove();
        }
    }
}

void ShellUSB::on_help_btn_clicked()
{

}
