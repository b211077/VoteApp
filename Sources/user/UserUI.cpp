// Class        : UserUI
// Description  : 회원 시스템의 boundary class
//                사용자는 UI를 통해 회원가입, 로그인, 로그아웃, 회원탈퇴 기능을 요청할 수 있다.
// Created      : 2017/6/16 20:00
// Author       : 허산
// Mail         : sanheo@me.com

#include <iostream>
#include <sstream>
#include "UserUI.h"
#include "User.h"
#include "UserControl.h"
#include "../data/Datetime.h"

using namespace std;

void UserUI::requestSignup() {
    clearScreen();
    showMessage("회원가입 과정을 시작합니다. 아래 정보를 입력해 주세요.");
    
    string userID = "";
    while (true) {
        userID = inputString("아이디");
        if (UserControl::canSignup(userID)) {
            break;
        } 
		else {
            showMessage("이미 존재하는 아이디입니다. 다른 아이디를 입력해주세요.");
        }
    }
    User * user = User::create(userID);
    
    string password = "";
    while (true) {
        password = inputString("비밀번호");
        if (strlen(password.c_str()) >= 6) {
            break;
        } else {
            showMessage("너무 짧은 비밀번호입니다. 6자리 이상 입력해주세요.");
        }
    }
    user->password = password;
    
    user->name = inputString("이름");
    
    while (true) {
        user->birthday = inputString("생년월일 (6자리)");
        if (Datetime::isValidDate(user->birthday)) {
            break;
        } else {
            showMessage("잘못된 날짜입니다. 다시 입력해주세요.");
        }
    }
    
    user->address = inputString("주소");
    user->email = inputString("이메일");
    
    // 회원가입 요청
    bool success = UserControl::signup(user);
    if (success) {
        showMessage("회원가입이 완료되었습니다.");
        freeze(1);
    } else {
        delete user;
        if (inputBool("다시 시도하시겠습니까?")) {
            UserUI::requestSignup();
        }
    }
}

void UserUI::requestWithdraw() {
    if (UserControl::hasActiveSession() == false) {
        showMessage("로그인이 필요합니다.");
        freeze(1);
        return;
    }
    clearScreen();
    if (inputBool("정말 탈퇴하시겠습니까?")) {
        string password = inputString("비밀번호를 입력해주세요");
        bool success = UserControl::withdraw(password);
        if (success) {
            showMessage("성공적으로 탈퇴되었습니다.");
        } else {
            showMessage("비밀번호가 일치하지 않습니다.");
        }
        freeze(1);
    }
}

void UserUI::requestLogin() {
    clearScreen();
    cout << "로그인을 시작합니다. 아래 정보를 입력해 주세요." << endl;
    string userID = inputString("아이디");
    string password = inputString("비밀번호");
    
    User * user = UserControl::login(userID, password);
    if (user != nullptr) {
        cout << user->getUserID() << "님, 로그인 되었습니다." << endl;
        freeze(1);
    } else {
        showMessage("잘못된 아이디 혹은 비밀번호입니다.");
        if (inputBool("다시 시도하시겠습니까?")) {
            UserUI::requestLogin();
        }
    }
}

void UserUI::requestLogout() {
    if (UserControl::hasActiveSession() == false) {
        showMessage("로그인이 필요합니다.");
        freeze(1);
        return;
    }
    clearScreen();
    if (inputBool("정말 로그아웃 하시겠습니까?")) {
        UserControl::logout();
        showMessage("로그아웃 되었습니다.");
        freeze(1);
    }
}

void UserUI::requestChangeSession() {
    clearScreen();
    showMessage("----- 세션 목록 -----");
    vector<string> users = UserControl::getSessionList();
    if (users.empty()) {
        showMessage("로그인된 사용자가 없습니다.");
        freeze(1);
        return;
    }
    
    int i=1;
    for (auto iter = users.begin(); iter != users.end(); ++iter) {
        cout << i << ". " << *iter << endl;
        i++;
    }
    int select = 0;
    while (true) {
        select = inputInteger("원하는 계정의 번호를 입력하세요.");
        if (0 < select && select < i) {
            break;
        } else {
            showMessage("잘못된 입력입니다.");
        }
    }
    
    string userID = users[select-1];
    string password = inputString(userID+"의 비밀번호를 입력해주세요.");
    
    User * user = UserControl::login(userID, password);
    if (user != nullptr) {
        cout << user->getUserID() << "님, 로그인 되었습니다." << endl;
        freeze(2);
    } else {
        showMessage("잘못된 비밀번호입니다.");
        if (inputBool("다시 시도하시겠습니까?")) {
            UserUI::requestChangeSession();
        }
    }
}
