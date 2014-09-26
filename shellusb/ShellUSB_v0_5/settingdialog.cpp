#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(noMatchPwd()), this, SLOT(repaint()));

    ui->enc_url->setText("./shell/enc");
    ui->dec_url->setText("./shell/dec");

    // dark fusion 테마
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
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

/**
 * @brief shellusb.bin에 필요한 설정 내용을 저장
 */
void SettingDialog::writeSysFile()
{
    QFile file;
    file.setFileName("./shell/sys/shellusb.bin");
    file.open(QFile::ReadWrite|QFile::Text);
    QTextStream out(&file);

    // 설정 파일에 저장
    out << "#directory of enc & dec";
    out << endl;
    out << "enc:" << this->encUrl + "\n";
    out << "dec:" << this->decUrl + "\n";
    out << "#encrypt byte\n";
    out << "bit:" << this->encrypt + "\n";
    out << "#password auto\n";
    out << "autopwd:" << this->pwdchk + "\n";
    out << "#writing log file\n";
    out << "flag:" << this->flag + "\n";

    if (this->flag == "1")
    {
        out << "#delete of log file\n";
        out << "period:" << this->period + "\n";
    }

    file.close();
}

/**
 * @brief shellpiece.bin에 패스워드를 암호화하여 저장
 */
void SettingDialog::writePwdFile()
{
    // 암호 파일 저장
    TinyAES crypto;
    QByteArray key = crypto.HexStringToByte("1234");
    QByteArray encPwd = crypto.Encrypt(this->firstPwd.toLocal8Bit(), key);
    QFile file;
    file.setFileName("./shell/sys/shellpiece.bin");

    // 파일 오픈 실패 시
    if (!file.open(QFile::WriteOnly)){
        return;
    }
    file.write(encPwd);
    file.close();
}

void SettingDialog::on_log_use_clicked()
{
    ui->log_period->setDisabled(false);
}

void SettingDialog::on_log_not_use_clicked()
{
    ui->log_period->setDisabled(true);
}

/**
 * @brief enc_url 경로를 수정하는 이벤트 처리 함수
 */
void SettingDialog::on_encpath_btn_clicked()
{
    QFileDialog dialog(this);
    QString path = ui->enc_url->text();

    if (path.size() == 0)
    {
        path = "C:/";
    }

    QString dirPath = dialog.getExistingDirectory(this, "암호화한 파일을 저장할 경로를 지정해주세요.", path);

    if (dirPath.size() > 0)
    {
        ui->enc_url->setText(dirPath);
    }
}

/**
 * @brief dec_url 경로를 수정하는 이벤트 처리 함수
 */
void SettingDialog::on_decpath_btn_clicked()
{
    QFileDialog dialog(this);
    QString path = ui->dec_url->text();

    if (path.size() == 0)
    {
        path = "C:/";
    }

    QString dirPath = dialog.getExistingDirectory(this, "암호화를 푼 파일을 저장할 경로를 지정해주세요.", path);

    if (dirPath.size() > 0)
    {
        ui->dec_url->setText(dirPath);
    }
}

/**
 * @brief 확인 버튼 클릭 시 이벤트 처리 함수
 */
void SettingDialog::on_submit_btn_clicked()
{
    // 비밀번호 확인
    this->firstPwd = ui->password->text();
    this->secondPwd = ui->password_2->text();

    if (this->firstPwd != this->secondPwd || (this->firstPwd.isEmpty() || this->secondPwd.isEmpty()))
    {
        QMessageBox::warning(this, "Warning","NO MATCH PASSWORD.");
        emit(noMatchPwd());
        return;
    }

    // 디렉토리 경로
    this->encUrl = ui->enc_url->text();
    this->decUrl = ui->dec_url->text();

    // 오토 키 사용 여부 확인
    if (ui->pwd_chk->isChecked())
        this->pwdchk = "1";
    else
        this->pwdchk = "0";

    // AES bit 선택
    if (ui->aes_256->isChecked())
    {
        this->encrypt = "256";
    }
    else
    {
        this->encrypt = "128";
    }

    // 로그 기록 사용 여부 확인
    if (ui->log_use->isChecked())
    {
        this->flag = "1";

        if (ui->log_period->currentText().compare("No Notice") == 0)
            this->period = "0";
        else
            this->period = ui->log_period->currentText();
    }
    else
    {
        this->flag = "0";
    }

    this->writeSysFile();
    this->writePwdFile();

    emit(close());
}
