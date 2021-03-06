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
    ui->front_btn->setDisabled(true);
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

    //treeview 초기 설정.
    index = dirModel->index(SetUp::encUrl);

    ui->treeView->setModel(dirModel);
    ui->treeView->setColumnHidden(1,true);
    ui->treeView->setColumnHidden(2,true);
    ui->treeView->setColumnHidden(3,true);
    ui->treeView->setCurrentIndex(index);

    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot|QDir::AllEntries);
    fileModel->setRootPath(SetUp::encUrl);

    //tableview 초기 설정.
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
        return;
    }

    QByteArray key;

    // 오토 키 여부 검사
    // 오토 키가 아니라면
    if (!SetUp::autopwd)
    {
        // 키 입력
        key = crypto.HexStringToByte
                (QInputDialog::getText(NULL, "Locking", "Input a locking key",
                                    QLineEdit::Password, NULL, &ok));

        // ok 버튼 눌렀는지 검사
        if (!ok)
        {
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
            QMessageBox::warning(NULL, "Warning", "Locking key is not same");
            if (SetUp::logFlag)
            {
                LogThread *log = new LogThread("ERROR//Locking key is not same",this);
                connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
                log->start();
            }
            return;
        }

    }
    // 오토 키가 맞다면
    else
    {
        key = crypto.HexStringToByte(SetUp::pwd);
    }

    // 키 암호화하여 파일에 저장하고 진행
    TinyAES crypto;

    // 키 암호화
    QByteArray encPwd = crypto.Encrypt(key, key);

    QFile file;
    QString fileName = fileModel->fileInfo(index).fileName();
    file.setFileName("./shell/sys/list/" + fileName);

    // 파일 오픈 실패 시
    if (!file.open(QFile::WriteOnly))
        return;

    file.write(encPwd);
    file.close();

    // 로그 기록
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
        return;
    }

    QByteArray key;

    TinyAES crypto;
    QByteArray encPwd;
    QFile file;

    // 파일 이름 가져오기
    QString srcFile = fileModel->fileInfo(index).fileName();
    lastDot = srcFile.lastIndexOf(".");
    QString fileName = srcFile.mid(0, lastDot);

    file.setFileName("./shell/sys/list/" + fileName);

    // 파일 오픈 실패 시
    if (!file.open(QFile::ReadOnly)){
        if (SetUp::logFlag)
        {
            LogThread *log = new LogThread("ERROR//File open fail. [ "+ file.fileName() + " ]",this);
            connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
            log->start();
        }
        return;
    }

    // 오토 키 여부 검사
    // 오토 키가 아니라면
    if (!SetUp::autopwd)
    {
        // 키 입력
        key = crypto.HexStringToByte
                (QInputDialog::getText(NULL, "Unlocking", "Input a unlocking key", QLineEdit::Password, NULL, &ok));

        // ok 버튼 눌렀는지 검사
        if (!ok)
        {
            if (SetUp::logFlag)
            {
                LogThread *log = new LogThread("CANCELED//Insert password.",this);
                connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
                log->start();
            }

            return;
        }

        // 파일을 복호화하여 키 읽기
        QByteArray data = file.readAll();

        file.close();

        // 암호화된 키 복호화
        QByteArray encKey = crypto.Decrypt(data, key);

        // 키 같은지 확인
        // 틀리면 경고창
        if (strcmp(key, encKey))
        {
            QMessageBox::warning(NULL, "Warning", "Locking key is not passed");
            if (SetUp::logFlag)
            {
                LogThread *log = new LogThread("ERROR//Locking key is not same",this);
                connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
                log->start();
            }
            return;
        }
    }
    // 오토 키가 맞다면
    else
    {
        key = crypto.HexStringToByte(SetUp::pwd);
    }

    // 파일 삭제 후 진행
    file.remove();

    // 로그 기록
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
        QString path = fileModel->fileInfo(index).absoluteFilePath();

        this->modifyList(path);
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

        // 로그 기록
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
        QString newPath = dirModel->filePath(treeIndex);

        this->modifyList(newPath);

        // treeView에서 선택한 위치로 tableView 이동
        ui->tableView->setRootIndex(fileModel->setRootPath(path));

        // back버튼 활성화/ front버튼 비활성화
        ui->back_btn->setDisabled(false);
        ui->front_btn->setDisabled(true);
    }
}

/**
 * @brief tableview의 오른쪽 클릭에 대한 이벤트.
 * @param pos: 마우스 이벤트가 발생한 위치.
 */
void ShellUSB::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex idx = ui->tableView->indexAt(pos);
    QPoint globalPos = ui->tableView->viewport()->mapToGlobal(pos);

    //배경에 마우스 포인터를 위치시키고 오른쪽 클릭을 했을때.
    if (fileModel->fileInfo(idx).path().compare(".") == 0)
        return;

    //메뉴 등록.
    QMenu menu;
    menu.addAction("Run");
    menu.addAction("remove");

    //마우스의 위치에 menu를 실행시키고 선택한 값을 selectedItem에 저장.
    QAction* selectedItem = menu.exec(globalPos);

    if (selectedItem)
    {
        QString select = selectedItem->text();

        // 실행 선택 시
        if (select.compare("Run") == 0)
        {

        }
        // 삭제 선택 시
        else if (select.compare("remove") == 0)
        {
            QFile file(fileModel->fileInfo(idx).absoluteFilePath());
            file.remove();
            if (SetUp::logFlag)
            {
                LogThread *log = new LogThread("WARNING//delete file [ "+fileModel->fileInfo(idx).absoluteFilePath() + " ]",this);
                connect(log, SIGNAL(finished()), log, SLOT(deleteLater()));
                log->start();
            }
        }
    }
}

// 만든이 보여주기
void ShellUSB::on_help_btn_clicked()
{
    helpDialog help;
    help.setModal(true);
    help.exec();
}

void ShellUSB::on_encurl_btn_clicked()
{
    QModelIndex idx;
    idx = this->fileModel->setRootPath(SetUp::encUrl);
    ui->tableView->setRootIndex(idx);
    idx = this->dirModel->setRootPath(SetUp::encUrl);
    ui->treeView->setCurrentIndex(idx);

    this->modifyList(SetUp::encUrl);

    // back버튼 활성화/ front버튼 비활성화
    ui->back_btn->setDisabled(false);
    ui->front_btn->setDisabled(true);
}

void ShellUSB::on_dncurl_btn_clicked()
{
    QModelIndex idx;
    idx = this->fileModel->setRootPath(SetUp::decUrl);
    ui->tableView->setRootIndex(idx);
    idx = this->dirModel->setRootPath(SetUp::decUrl);
    ui->treeView->setCurrentIndex(idx);

    this->modifyList(SetUp::decUrl);

    // back버튼 활성화/ front버튼 비활성화
    ui->back_btn->setDisabled(false);
    ui->front_btn->setDisabled(true);
}

void ShellUSB::modifyList(const QString path){
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

    // lt 뒤가 새로운 경로가 아니라면
    if (lt->back() != path)
    {
        lt->push_back(path);
        iter = lt->rbegin();
    }
}
