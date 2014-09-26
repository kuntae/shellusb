#include "setup.h"

//암호화 & 복호화 디렉토리를 저장하는 정적변수.
QString SetUp::encUrl;
QString SetUp::decUrl;

//암호화 & 복호화를 할 때 사용할 KEY bit 수.
int SetUp::bit;

//파일 암호화 & 복호화 시 추가 비밀번호를 사용할지를 정하는 flag 변수.
int SetUp::autopwd;

//로그를 사용할지 정하는 flag 변수.
int SetUp::logFlag;
//로그를 몇 MB까지 저장할 지 정하는 변수.
int SetUp::period;

//로그인 비밀번호를 저장하고 있는 변수.
QString SetUp::pwd;

SetUp::SetUp()
{
}

SetUp::~SetUp()
{
}
