#ifndef SETUP_H
#define SETUP_H

#include <QString>
#include <QDebug>
#include <QHash>

class SetUp
{
public:
    //setting variable.
    static QString encUrl;
    static QString decUrl;
    static int bit;
    static QString lang;
    static int logFlag;
    static int period;
    static QString pwd;
    static QHash<QString, QString> pwdlist;
    explicit SetUp();
    ~SetUp();
};

#endif // SETUP_H
