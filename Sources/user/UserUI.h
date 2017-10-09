// Class        : UserUI
// Description  : 회원 시스템의 boundary class
//                사용자는 UI를 통해 회원가입, 로그인, 로그아웃, 회원탈퇴 기능을 요청할 수 있다.
// Created      : 2017/6/16 20:00
// Author       : 허산
// Mail         : sanheo@me.com

#pragma once

#include "../Boundary.h"

class UserUI : public Boundary {
public:

    // Function     : void requestSignup()
    // Description  : 회원가입 과정을 시작합니다.
    // Parameters   : none
    // Return Value : none
    static void requestSignup();
    
    // Function     : void requestWithdraw()
    // Description  : 회원탈퇴 과정을 시작합니다.
    // Parameters   : none
    // Return Value : none
    static void requestWithdraw();
    
    // Function     : void requestLogin()
    // Description  : 로그인 과정을 시작합니다.
    // Parameters   : none
    // Return Value : none
    static void requestLogin();
    
    // Function     : void requestLogout()
    // Description  : 로그아웃 과정을 시작합니다.
    // Parameters   : none
    // Return Value : none
    static void requestLogout();
    
    // Function     : void requestChangeSession()
    // Description  : 세션변경을 시작합니다.
    // Parameters   : none
    // Return Value : none
    static void requestChangeSession();
};
