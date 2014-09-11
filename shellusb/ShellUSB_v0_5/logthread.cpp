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
}

void LogThread::setLogFileName(QString str){
  logFileName = str;
}

