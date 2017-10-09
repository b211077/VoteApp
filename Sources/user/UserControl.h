// Class        : UserControl
// Description  : 회원 시스템의 control class
//                회원가입, 로그인, 로그아웃, 회원탈퇴 기능을 처리한다.
// Created      : 2017/6/19 18:00
// Author       : 허산
// Mail         : sanheo@me.com

#pragma once

#include <iostream>
#include <vector>
#include "User.h"

class UserControl {
public:
    // Function     : bool signup(User *)
    // Description  : 회원가입을 수행합니다. 회원가입이 성공하면 세션에 로그인됩니다.
    // Parameters   : User * user   회원가입을 진행할 사용자 객체
    // Return Value : bool          회원가입 성공 여부
    static bool signup(User * user);
    
    // Function     : bool withdraw(string)
    // Description  : 현재 로그인된 사용자에 대해 회원탈퇴를 수행합니다.
    // Parameters   : string    현재 로그인된 사용자가 입력한 비밀번호
    // Return Value : bool      회원탈퇴 성공 여부
    static bool withdraw(std::string password);
    
    // Function     : User * login(string, string)
    // Description  : 로그인을 수행합니다.
    // Parameters   : string userID     사용자 아이디
    //                string password   비밀번호
    // Return Value : 로그인 성공시 User instance, 실패시 nullptr 반환
    static User * login(std::string userID, std::string password);
    
    // Function     : void logout()
    // Description  : 현재 로그인된 사용자에 대해 로그아웃을 수행합니다.
    // Parameters   : none
    // Return Value : none
    static void logout();
    
    // Function     : bool canSignup(string)
    // Description  : 가입할 수 있는 아이디인지 확인합니다.
    // Parameters   : string userID 확인 할 아이디
    // Return Value : bool          중복된 아이디인 경우 false
    static bool canSignup(std::string userID);
    
    // Function     : bool hasActiveSession()
    // Description  : 로그인된 세션이 있는지 여부를 반환합니다.
    // Parameters   : none
    // Return Value : bool  로그인 여부
    static bool hasActiveSession();
    
    // Function     : vector<string> getSessionList()
    // Description  : 로그인된 사용자들의 아이디 목록을 불러옵니다.
    // Parameters   : none
    // Return Value : vector<string>  사용자 아이디 목록
    static std::vector<std::string> getSessionList();
};
