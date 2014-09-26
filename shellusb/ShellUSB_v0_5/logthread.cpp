#include "logthread.h"

QString LogThread::logFileName;

LogThread::LogThread( QString str, QObject *parent):QThread(parent), msg(str)
{
}

LogThread::~LogThread()
{
}
/**
 * @brief thread 클래스의 run()함수를 오버로딩함.
 * 파일의 뒤에 내용을 계속해서 추가함.
 */
void LogThread::run()
{
  QString timeStr;

  file.setFileName(this->logFileName);
  file.open(QFile::ReadWrite|QFile::Append|QFile::Text);
  QTextStream st(&file);
  time = QTime::currentTime();
  timeStr = QString("%1:%2:%3 ").arg(QString::number(time.hour()),
                                     QString::number(time.minute()),
                                     QString::number(time.second()));
  timeStr.append(msg+"\n");
  st << timeStr;
  file.close();
}
/**
 * @brief 로그파일의 이름을 설정하는 Setter.
 * @param str: 파일 이름.
 */
void LogThread::setLogFileName(QString str)
{
  logFileName = str;
}

