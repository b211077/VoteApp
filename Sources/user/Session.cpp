// Class        : Session
// Description  : 사용자들의 세션을 관리하는 클래스. 싱글톤 패턴으로 구현.
// Created      : 2017/6/19 17:00
// Author       : 허산
// Mail         : sanheo@me.com

#include <iostream>
#include "Session.h"

using namespace std;

static Session * instance = nullptr;

Session * Session::getInstance() {
    if (!instance) {
        instance = new Session();
    }
    return instance;
}

// 세션 생성자
Session::Session()
:currentUser(nullptr)
,activeUsers()
{

}

// 세션 소멸자
Session::~Session()
{
    if (currentUser != nullptr) {
        delete currentUser;
        currentUser = nullptr;
    }
}

// 사용자의 세션을 활성화하고, 현재 로그인된 사용자로 설정합니다.
void Session::activateUser(User *user) {
    activeUsers[user->getUserID()] = user;
    currentUser = user;
}

// 사용자의 세션을 비활성화합니다.
void Session::deactivateUser(User *user) {
    if (user == nullptr) {
        return;
    }
    string userID = user->getUserID();
    if (user == currentUser) {
        currentUser = nullptr;
    }
    activeUsers.erase(userID);
}

// 현재 로그인된 사용자 객체를 반환합니다.
User * Session::getCurrentUser() {
    return currentUser;
}
