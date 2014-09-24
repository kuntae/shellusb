#include "setup.h"

//directory.
QString SetUp::encUrl;
QString SetUp::decUrl;

//encrypt byte.
int SetUp::bit;

//lenguage.
QString SetUp::lang;

//log
int SetUp::logFlag;
int SetUp::period;

//password
QString SetUp::pwd;
QHash<QString, QString> SetUp::pwdlist;
SetUp::SetUp()
{

}

SetUp::~SetUp(){

}
