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
    ui->log_period->setDisabled(true);
    ui->file_system->setDisabled(true);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButton_3_clicked()
{
    //password check.
    QString first = ui->password->text();
    QString second = ui->password_2->text();

    if(first != second || (first.isEmpty() || second.isEmpty())){
        qDebug() << "no match";
        emit(noMatchPwd());
        return;
    }
    //directory path.
    QString enc = ui->enc_url->text();
    QString dec = ui->dec_url->text();

    //lenguage.
    QString lang = ui->language->currentText();
    //encrypt byte & log flag.
    QString encrypt;
    QString flag;
    if(ui->aes_128->isChecked()){
        encrypt = "128";
    }else{
        encrypt = "256";
    }
    QString period;
    if(ui->log_use->isChecked()){
        flag = "1";
        period = ui->log_period->currentText();
    }else{
        flag = "0";
    }

    QFile file;
    file.setFileName("./shell/sys/shellusb.bin");
    file.open(QFile::ReadWrite|QFile::Text);
    QTextStream out(&file);

    //write file.
    out << "#directory of enc & dec";
    out << endl;
    out << enc + "\n";
    out << dec + "\n";
    out << "#encrypt byte\n";
    out << encrypt + "\n";
    out << "#language\n";
    out << lang + "\n";
    out << "#writing log file\n";
    out << flag + "\n";
    if(flag == "1"){
        out << "#delete of log file\n";
        out << period + "\n";
    }
    file.close();

    //write password file.
    TinyAES crypto;
    QByteArray key = crypto.HexStringToByte("1234");
    QByteArray encPwd = crypto.Encrypt(first.toUtf8(), key);
    QFile pwdFile;
    pwdFile.setFileName("./shell/sys/shellpiece.bin");
    if(!pwdFile.open(QFile::WriteOnly)) qDebug()<<__FILEW__ <<" password file";
    pwdFile.write(encPwd);
    pwdFile.close();

    emit(close());
}

void SettingDialog::on_log_use_clicked()
{
    ui->log_period->setDisabled(false);
}

void SettingDialog::on_log_not_use_clicked()
{
    ui->log_period->setDisabled(true);
}
