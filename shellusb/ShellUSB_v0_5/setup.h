#ifndef SETUP_H
#define SETUP_H

#include <QString>
#include <QDebug>

//모든 클래스에서 초기 설정 이외에는 변경되지 않는 값을 사용함.
//static 으로 선언하여 변수가 중복생성 되지 않도록함.
class SetUp
{
public:
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
