#ifndef LOGTHREAD_H
#define LOGTHREAD_H
#include <QThread>
#include <QtCore>
#include <QString>
#include <QDebug>
#include <QString>
#include <QDate>
#include <QFile>

class LogThread:public QThread
{
    Q_OBJECT

public:
  static QString logFileName;
  explicit LogThread(QString str, QObject *parent = 0);
  ~LogThread();
  static void setLogFileName(QString str);
    void run();
protected:


signals:
    void test();

private slots:

private:
  QString msg;
  QDate date;
  QFile file;
};

#endif // LOGTHREAD_H
