#include "logthread.h"

QString LogThread::logFileName;

LogThread::LogThread(QString str):QThread(), msg(str)
{
  connect( this, SIGNAL(finished()), this, SLOT(deleteLater()) );
}

LogThread::~LogThread(){
  qDebug()<<"die log thread.";
}

void LogThread::run(){
  qDebug()<<"runnig log thread.";
}

void LogThread::setLogFileName(QString str){
  logFileName.append(str);
}

