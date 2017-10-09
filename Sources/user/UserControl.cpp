// Class        : UserControl
// Description  : 회원 시스템의 control class
//                회원가입, 로그인, 로그아웃, 회원탈퇴 기능을 처리한다.
// Created      : 2017/6/19 18:00
// Author       : 허산
// Mail         : sanheo@me.com

#include <iostream>
#include "../data/DataManager.h"
#include "UserControl.h"
#include "Session.h"

using namespace std;

// 현재 로그인된 사용자에 대해 회원탈퇴를 수행합니다.
bool UserControl::withdraw(std::string password) {
    User * user = Session::getInstance()->getCurrentUser();
    if (user != nullptr && user->checkPassword(password)) {
        // 로그아웃
        Session::getInstance()->deactivateUser(user);
        // 회원삭제
        DataManager::getInstance()->deleteUser(user);
        return true;
    }
    return false;
}

// 회원가입을 요청합니다. 회원가입이 성공하면 세션에 로그인됩니다.
bool UserControl::signup(User *user) {
    // 사용자 객체가 없으면 실패
    if (user == nullptr) { return false; }
    // 데이터 관리자를 불러옴
    auto data = DataManager::getInstance();
    // 이미 존재하는 아이디가 아닌 경우, 회원정보 저장
    if (data->getUser(user->getUserID()) == nullptr) {
        data->addUser(user);
    } else {
        cout << "이미 존재하는 아이디입니다." << endl;
        return false;
    }
    // 로그인 처리
    Session::getInstance()->activateUser(user);
    // 회원가입 완료
    return true;
}

// 로그인을 수행합니다.
User * UserControl::login(string userID, string password) {
    auto data = DataManager::getInstance();
    // 사용자 객체를 불러온다.
    User * user = data->getUser(userID);
    // 비밀번호를 확인한다.
    if (user != nullptr && user->checkPassword(password)) {
        // 로그인 처리
        Session::getInstance()->activateUser(user);
        return user;
    }
    return nullptr;
}

// 현재 로그인된 사용자에 대해 로그아웃을 수행합니다.
void UserControl::logout() {
    auto session = Session::getInstance();
    User * user = session->getCurrentUser();
    session->deactivateUser(user);
}

// 가입할 수 있는 아이디인지 확인합니다.
bool UserControl::canSignup(string userID) {
    return true;
}

// 로그인된 세션이 있는지 여부를 반환합니다.
bool UserControl::hasActiveSession() {
    auto session = Session::getInstance();
    User * user = session->getCurrentUser();
    return (user != nullptr);
}

// 로그인된 사용자 목록을 불러옵니다.
vector<string> UserControl::getSessionList() {
    vector<string> ret = vector<string>();
    auto session = Session::getInstance();
    for (auto iter = session->activeUsers.cbegin();
         iter != session->activeUsers.cend(); ++iter) {
        User * user = iter->second;
        ret.push_back(user->getUserID());
    }
    return ret;
}
