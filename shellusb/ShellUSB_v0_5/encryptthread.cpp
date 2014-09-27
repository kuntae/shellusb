#include "encryptthread.h"

#include <QDebug>
#include <QApplication>

EncryptThread::EncryptThread(QObject *parent):
    QThread(parent)
{
    this->stop = false;
}

// 파일 경로, 키, 플래그 저장
void EncryptThread::init(QString filePath, QByteArray key, bool cryptFlag)
{
    this->filePath = filePath;
    this->key = key;
    this->cryptFlag = cryptFlag;
}

EncryptThread::~EncryptThread()
{
}

// 함수 호출로 run 메소드 실행
void EncryptThread::run()
{
    if (this->cryptFlag)
        encrypt();
    else
        decrypt();
}

void EncryptThread::encrypt()
{
    QMutex mutex;
    const int size = SetUp::bit; // 설정한 bit로 암호화

    // 소스 파일 경로 설정
    QString srcPath = this->filePath;
    QFile srcFile(srcPath);

    // 타겟 파일 경로 설정
    QString tgtPath;

    // encUrl이 유효하면 encUrl을 사용
    if (SetUp::encUrl.size() > 0)
    {
        QFileInfo srcFileInfo(srcFile.fileName());
        tgtPath = SetUp::encUrl + "/" + srcFileInfo.fileName();
    }
    // encUrl이 유효하지 않으면 현재 폴더에 암호화한다.
    else
    {
        tgtPath = srcPath;
    }

    // 확장자 추가
    tgtPath = tgtPath + ".ShellUSB";
    QFile tgtFile(tgtPath);

    // 키 설정
    QByteArray key = this->key;

    // 소스 파일과 타겟 파일 열기
    if (!srcFile.open(QFile::ReadOnly))
    {
        return;
    }

    if (!tgtFile.open(QFile::WriteOnly))
    {
        return;
    }

    // 버퍼를 128byte 크기로 설정
    QByteArray buffer;
    buffer.resize(size);

    QByteArray encrypted;

    int count = 0;
    int presentSize = 0;
    int onePercentSize = srcFile.size() / 100;
    int finalSize = onePercentSize;

    // 소스 파일을 읽은 후 암호화하여 타겟 파일에 저장
    while (!srcFile.atEnd())
    {
        // critical section
        mutex.lock();
        if (this->stop)
        {
            break;
        }
        mutex.unlock();

        buffer = srcFile.read(size);
        encrypted = crypto.Encrypt(buffer, key);
        tgtFile.write(encrypted);

        // progressbar 업데이트
        presentSize += buffer.size();

        if (presentSize > finalSize)
        {
            finalSize += onePercentSize;
            count++;
        }

        emit sinalUpdate(count);
    }

    // 소스 파일 닫기
    srcFile.close();

    // 타겟 파일 닫기
    tgtFile.flush();
    tgtFile.close();

    // 비정상적으로 종료된 경우
    if (this->stop)
    {
        // 타겟 파일을 삭제
        tgtFile.remove();
    }
    // 정상적으로 종료된 경우
    else
    {
        // 소스 파일을 삭제
        srcFile.remove();
    }
}

void EncryptThread::decrypt()
{
    QMutex mutex;
    const int size = SetUp::bit + 32; // 설정한 bit로 암호화

    // 소스 파일 경로 설정
    QString srcPath = this->filePath;
    QFile srcFile(srcPath);

    // 타겟 파일 경로 설정
    QString tgtPath;

    // decUrl이 유효하면 decUrl을 사용
    if (SetUp::decUrl.size() > 0)
    {
        QFileInfo srcFileInfo(srcFile.fileName());
        tgtPath = SetUp::decUrl + "/" + srcFileInfo.fileName();
        int lastDot = tgtPath.lastIndexOf(".");
        tgtPath = tgtPath.mid(0, lastDot);
    }
    // decUrl이 유효하지 않으면 현재 폴더에 암호화한다.
    else
    {
        int lastDot = srcPath.lastIndexOf(".");
        tgtPath = srcPath.mid(0, lastDot);
    }

    QFile tgtFile(tgtPath);

    // 키 설정
    QByteArray key = this->key;

    // 소스 파일과 타겟 파일 열기
    if (!srcFile.open(QFile::ReadOnly))
    {
        return;
    }

    if (!tgtFile.open(QFile::WriteOnly))
    {
        return;
    }

    // 버퍼를 128 + 32 = 160byte 크기로 설정
    QByteArray buffer;
    buffer.resize(size);

    QByteArray decrypted;

    int count = 0;
    int presentSize = 0;
    int onePercentSize = srcFile.size() / 100;
    int finalSize = onePercentSize;

    // 소스 파일을 읽은 후 복호화하여 타겟 파일에 저장
    while (!srcFile.atEnd())
    {
        // critical section
        mutex.lock();
        if (this->stop)
        {
            break;
        }
        mutex.unlock();

        buffer = srcFile.read(size);
        decrypted = crypto.Decrypt(buffer, key);
        tgtFile.write(decrypted);

        // progressbar 업데이트
        presentSize += buffer.size();

        if (presentSize > finalSize)
        {
            finalSize += onePercentSize;
            count++;
        }

        emit sinalUpdate(count);
    }

    // 소스 파일 닫기
    srcFile.close();

    // 타겟 파일 닫기
    tgtFile.flush();
    tgtFile.close();

    // 비정상적으로 종료된 경우
    if (this->stop)
    {
        // 타겟 파일을 삭제
        tgtFile.remove();
    }
    // 정상적으로 종료된 경우
    else
    {
        // 소스 파일을 삭제
        srcFile.remove();
    }
}

// 쓰레드 취소
void EncryptThread::cancelThread()
{
    return;
}
