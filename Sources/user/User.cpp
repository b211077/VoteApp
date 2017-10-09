// Class        : User
// Description  : 회원 데이터를 갖는 entity class
// Created      : 2017/6/19 16:00
// Author       : 허산
// Mail         : sanheo@me.com

#include "User.h"

using namespace std;

User * User::create(string userID) {
    User * user = new User(userID);
    return user;
}

User::User(string userID)
:userID(userID)
{
}

User::~User()
{
}

// 사용자 아이디를 반환합니다.
const string& User::getUserID() {
    return this->userID;
}

// 비밀번호가 일치하는지 확인합니다.
bool User::checkPassword(string password) {
    return (this->password.compare(password) == 0);
}
