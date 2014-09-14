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

    ui->file_system->setDisabled(true);

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
    //this->setWindowFlags(Qt::FramelessWindowHint);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButton_3_clicked()
{
    //password check.
    this->firstPwd = ui->password->text();
    this->secondPwd = ui->password_2->text();

    if(this->firstPwd != this->secondPwd || (this->firstPwd.isEmpty() || this->secondPwd.isEmpty())){
        qDebug() << "no match";
        QMessageBox::information(this, "NO MATCH PASSWORD.","NO MATCH PASSWORD.");
        emit(noMatchPwd());
        return;
    }
    //directory path.
    this->encUrl = ui->enc_url->text();
    this->decUrl = ui->dec_url->text();

    //lenguage.
    this->lang = ui->language->currentText();

    //encrypt byte & log flag.
    if(ui->aes_256->isChecked()){
        this->encrypt = "256";
    }else{
        this->encrypt = "128";
    }

    if(ui->log_use->isChecked()){
        this->flag = "1";
        this->period = ui->log_period->currentText();
    }else{
        this->flag = "0";
    }

    this->writeSysFile();
    this->writePwdFile();

    emit(close());
}

void SettingDialog::writeSysFile(){
    QFile file;
    file.setFileName("./shell/sys/shellusb.bin");
    file.open(QFile::ReadWrite|QFile::Text);
    QTextStream out(&file);

    //write file.
    out << "#directory of enc & dec";
    out << endl;
    out << this->encUrl + "\n";
    out << this->decUrl + "\n";
    out << "#encrypt byte\n";
    out << this->encrypt + "\n";
    out << "#language\n";
    out << this->lang + "\n";
    out << "#writing log file\n";
    out << this->flag + "\n";
    if(this->flag == "1"){
        out << "#delete of log file\n";
        out << this->period + "\n";
    }
    file.close();
}

void SettingDialog::writePwdFile(){
    //write password file.
    TinyAES crypto;
    QByteArray key = crypto.HexStringToByte("1234");
    QByteArray encPwd = crypto.Encrypt(this->firstPwd.toLocal8Bit(), key);
    QFile file;
    file.setFileName("./shell/sys/shellpiece.bin");
    if(!file.open(QFile::WriteOnly)) qDebug()<<__FILEW__ <<" password file";
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
