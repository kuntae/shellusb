#include "shellusb.h"
#include "ui_shellusb.h"

/**
 * @brief 생성자
 * @param parent
 */
ShellUSB::ShellUSB(QWidget *parent) :
    QDialog(parent), ui(new Ui::ShellUSB), lt(new std::list<QString>), iter(lt->rbegin())
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

    // 버튼 비활성화
    ui->front_btn->setDisabled(true); //if listFront !=NULL then front_btn enable else then front_btn disabled.
    ui->back_btn->setDisabled(true);

    // set icon images
    ui->back_btn->setIcon(QIcon(":/img/back.png"));
    ui->front_btn->setIcon(QIcon(":/img/front.png"));
    ui->help_btn->setIcon(QIcon(":/img/help.png"));

    QModelIndex index;
    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(SetUp::encUrl);

    // 맨처음 경로 저장
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

    // 파일 확장자 얻어 오기
    int lastDot = fileModel->fileInfo(index).absoluteFilePath().lastIndexOf(".");
    QString duplicated = fileModel->fileInfo(index).absoluteFilePath().mid(lastDot, 9);

    // 중복 여부 검사
    if (!duplicated.compare(".ShellUSB"))
    {
        QMessageBox::warning(NULL, "Warning", "This file is already encrypted");
        qDebug() << "duplicated";

        return;
    }

    // 키 입력
    QByteArray key = crypto.HexStringToByte
            (QInputDialog::getText(NULL, "Locking", "Input a locking key",
                                   QLineEdit::Password, NULL, &ok));

    // ok 버튼 눌렀는지 검사
    if (!ok)
    {
        qDebug() << "canceled";
        if (SetUp::logFlag)
        {
            LogThread *log = new LogThread("CANCELED//Insert password.",this);
            connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
            log->start();
        }

        return;
    }

    // 확인 키 입력
    QByteArray confirmKey = crypto.HexStringToByte
            (QInputDialog::getText(NULL, "Locking", "Input a same locking key again",
                                   QLineEdit::Password, NULL, &ok));

    // ok 버튼 눌렀는지 검사
    if (!ok)
    {
        qDebug() << "canceled";
        if (SetUp::logFlag)
        {
            LogThread *log = new LogThread("CANCELED//Insert password.",this);
            connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
            log->start();
        }

        return;
    }

    // 키 같은지 확인
    // 틀리면 경고창
    if (strcmp(key, confirmKey))
    {
        qDebug() << "password is not passed";
        QMessageBox::warning(NULL, "Warning", "Locking key is not same");
        return;
    }
    // 같으면 키 암호화하여 파일에 저장하고 진행
    else
    {
        TinyAES crypto;
        QByteArray encPwd = crypto.Encrypt(key, key);
        QFile file;
        QString fileName = fileModel->fileInfo(index).fileName();
        file.setFileName("./shell/sys/list/" + fileName);

        if (!file.open(QFile::WriteOnly))
            qDebug() << __FILEW__  << " password file";

        file.write(encPwd);
        file.close();
    }

    if (SetUp::logFlag)
    {
        LogThread *log = new LogThread("WARNING//Encryption file: [ " + fileModel->fileInfo(index).absoluteFilePath()+ " ]", this);
        connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
        log->start();
    }

    // ProgDialog 생성
    ProgDialog *progDialog = new ProgDialog(this);
    progDialog->init(fileModel->fileInfo(index).absoluteFilePath(), key, true);
    progDialog->show();
}

/**
 * @brief dec 버튼 클릭 시 이벤트 처리 함수
 */
void ShellUSB::on_dnc_btn_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();

    // 파일 확장자 얻어 오기
    int lastDot = fileModel->fileInfo(index).absoluteFilePath().lastIndexOf(".");
    QString duplicated = fileModel->fileInfo(index).absoluteFilePath().mid(lastDot, 9);

    // 중복 여부 검사
    if (duplicated.compare(".ShellUSB"))
    {
        QMessageBox::warning(NULL, "Warning", "This file is not encrypted");
        qDebug() << "duplicated";

        return;
    }

    // 키 입력
    QByteArray key = crypto.HexStringToByte
            (QInputDialog::getText(NULL, "Unlocking", "Input a unlocking key", QLineEdit::Password, NULL, &ok));

    // ok 버튼 눌렀는지 검사
    if (!ok)
    {
        qDebug() << "canceled";
        if (SetUp::logFlag)
        {
            LogThread *log = new LogThread("CANCELED//Insert password.",this);
            connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
            log->start();
        }

        return;
    }

    // 파일을 복호화하여 키 읽기
    TinyAES crypto;
    QByteArray encPwd;
    QFile file;
    QString srcFile = fileModel->fileInfo(index).fileName();
    lastDot = srcFile.lastIndexOf(".");
    QString fileName = srcFile.mid(0, lastDot);

    file.setFileName("./shell/sys/list/" + fileName);

    if (!file.open(QFile::ReadOnly))
        qDebug() <<  __FILEW__  << " password file";

    QByteArray data = file.readAll();

    file.close();

    QByteArray encKey = crypto.Decrypt(data, key);

    // 키 같은지 확인
    // 틀리면 경고창
    if (strcmp(key, encKey))
    {
        qDebug() << "password is not passed";
        QMessageBox::warning(NULL, "Warning", "Locking key is not passed");
        return;
    }
    // 같으면 파일 삭제하고 진행
    else
    {
        file.remove();
    }

    if (SetUp::logFlag)
    {
        LogThread *log = new LogThread("WARNING//Decryption file: [ " + fileModel->fileInfo(index).absoluteFilePath()+ " ]", this);
        connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
        log->start();
    }

    // ProgDialog 생성
    ProgDialog *progDialog = new ProgDialog(this);
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
        QString path = fileModel->fileInfo(index).absoluteFilePath();

        if (lt->back() != path)
            lt->push_back(path);

        // 더블클릭한 위치로 이동
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

        if (SetUp::logFlag)
        {
            LogThread *log = new LogThread("SUCCESSED//execute file: [ " + fileModel->fileInfo(index).absoluteFilePath()+ " ]", this);
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
        if (lt->back() != newPath)
        {
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

    if (fileModel->fileInfo(idx).path().compare(".") == 0)
        return;

    QMenu menu;
    menu.addAction("Run");
    menu.addAction("remove");

    QAction* selectedItem = menu.exec(globalPos);

    if (selectedItem)
    {
        QString select = selectedItem->text();
        if (select.compare("Run") == 0)
        {
            qDebug() <<"Run";
        }
        else if (select.compare("remove") == 0)
        {
            qDebug() <<"remove"<<fileModel->fileInfo(idx).absoluteFilePath();
            QFile file(fileModel->fileInfo(idx).absoluteFilePath());
            file.remove();
        }
    }
}

void ShellUSB::on_help_btn_clicked()
{
    helpDialog help;
    help.setModal(true);
    help.exec();
}
