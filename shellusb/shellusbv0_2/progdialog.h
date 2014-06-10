#ifndef PROGDIALOG_H
#define PROGDIALOG_H

#include <QDialog>

namespace Ui {
class progdialog;
}

class progdialog : public QDialog
{
    Q_OBJECT

public:
    explicit progdialog(QWidget *parent = 0);
    ~progdialog();

public slots:
    void on_pushButton_clicked();
    void onChangeNumber(int i);

private:
    Ui::progdialog *ui;
};

#endif // PROGDIALOG_H
