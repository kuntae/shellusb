#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QFileInfo>

#include <qmath.h>
#include <QPixmap>
#include <QPainter>
#include <QTime>
#include <QStyleFactory>

#include "logthread.h"
#include "setup.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

private:
    Ui::MainWindow *ui;
    static int failCnt;
    QString inText;
    QString getString(int length);
    QPixmap makeImg(QString);
    void distortImg(QPixmap);
};

#endif // MAINWINDOW_H
