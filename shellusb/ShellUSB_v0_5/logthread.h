#ifndef LOGTHREAD_H
#define LOGTHREAD_H
#include <QThread>
#include <QString>
#include <QDebug>
#include <QString>
#include <QDate>
#include  <QFile>

class LogThread:public QThread
{

public:
  static QString logFileName;
  explicit LogThread(QString str);
  ~LogThread();
  static void setLogFileName(QString str);
protected:
 void run();
private:
  QString msg;
  QDate date;
  QFile file;

};

#endif // LOGTHREAD_H
