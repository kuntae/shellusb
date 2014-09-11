#include "logthread.h"

QString LogThread::logFileName;

LogThread::LogThread( QString str, QObject *parent):QThread(parent), msg(str)
{
  //connect( this, SIGNAL(finished()), this, SLOT(deleteLater()) );
    qDebug() << "log thread created.";
}

LogThread::~LogThread(){
  qDebug()<<"die log thread.";
}

void LogThread::run(){
  qDebug()<<"runnig log thread.";
  qDebug()<<logFileName;
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

void LogThread::setLogFileName(QString str){
  logFileName = str;
}

