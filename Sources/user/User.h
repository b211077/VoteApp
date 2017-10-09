// Class        : User
// Description  : 회원 데이터를 갖는 entity class
// Created      : 2017/6/19 16:00
// Author       : 허산
// Mail         : sanheo@me.com

#pragma once

#include <iostream>

class User {
    
public:
    // Function     : User * create(string)
    // Description  : 사용자 객체를 생성합니다.
    // Parameters   : string    사용자 아이디
    // Return Value : User *    생성된 사용자 객체 포인터
    static User * create(std::string userID);
    
    // Function     : const string& getUserID()
    // Description  : 사용자 아이디를 반환합니다.
    // Parameters   : none
    // Return Value : string    현 객체의 사용자 아이디
    const std::string& getUserID();
    
    //
    // Function     : bool checkPassword(string)
    // Description  : 비밀번호가 일치하는지 확인합니다.
    // Parameters   : string    확인 할 비밀번호
    // Return Value : bool      비밀번호 일치 여부
    bool checkPassword(std::string password);
    
    // 비밀번호
    std::string password;
    
    // 이름
    std::string name;
    
    // 주민번호 앞 생년월일 6자리
    std::string birthday;
    
    // 주소
    std::string address;
    
    // 이메일
    std::string email;
    
    // 소멸자
    virtual ~User();
    
protected:
    // 생성자
    User(std::string userID);
    
    // 사용자 이름
    const std::string userID;
};
