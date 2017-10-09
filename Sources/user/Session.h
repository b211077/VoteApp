// Class        : Session
// Description  : 사용자들의 세션을 관리하는 클래스. 싱글톤 패턴으로 구현.
// Created      : 2017/6/19 17:00
// Author       : 허산
// Mail         : sanheo@me.com

#pragma once

#include <map>
#include "User.h"

class Session {
    
public:
    // Function     : Session * getInstance()
    // Description  : Session 클래스의 싱글턴 인스턴스를 불러옵니다.
    // Parameters   : none
    // Return Value : Session instance
    static Session* getInstance();
    
    // Function     : void activateUser(User * user)
    // Description  : 사용자의 세션을 활성화하고, 현재 로그인된 사용자로 설정합니다.
    // Parameters   : User *    로그인 할 사용자의 포인터
    // Return Value : none
    void activateUser(User * user);
    
    // Function     : void deactivateUser(User * user)
    // Description  : 사용자의 세션을 비활성화합니다.
    // Parameters   : User *    로그아웃 할 사용자의 포인터
    // Return Value : none
    void deactivateUser(User * user);
    
    // Function     : User * getCurrentUser()
    // Description  : 현재 로그인된 사용자 객체를 반환합니다.
    // Parameters   : none
    // Return Value : User instance. 로그인된 사용자가 없는 경우 nullptr.
    User * getCurrentUser();
    
    // 세션에 로그인된 사용자들
    std::map<std::string, User*> activeUsers;
    
private:
    
    // 생성자
    Session();
    
    // 소멸자
    ~Session();
    
    // 현재 로그인된 사용자
    User * currentUser;
    
};
