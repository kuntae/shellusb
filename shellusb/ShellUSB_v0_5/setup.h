#ifndef SETUP_H
#define SETUP_H

#include <QString>
#include <QDebug>

class SetUp
{
public:
    //setting variable.
    static QString encUrl;
    static QString decUrl;
    static int bit;
    static int autopwd;
    static int logFlag;
    static int period;
    static QString pwd;
    explicit SetUp();
    ~SetUp();
};

#endif // SETUP_H
