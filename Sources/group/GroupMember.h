// Class        : GroupMember
// Description  : 그룹 회원의 entity class
// Created      : 2017/6/16 22:00
// Author       : 주민범
// Mail         : meantiger91@gmail.com

#pragma once

#include "../user/User.h"


class GroupMember : public User {
public:
    // 사용자 객체를 생성합니다.
    static GroupMember * create(User * user);
    
    // 소멸자
    virtual ~GroupMember();
    
	// Function     : int getAuthority()
	// Description  : 유저의 권한을 반환합니다.
	// Parameters   : void
	// Return Value : int 유저의 권한.
    int getAuthority();
    
	// Function     : void setAuthority()
	// Description  : 유저의 권한을 변경합니다.
	// Parameters   : int authority 변경할려는 권한 정도
	// Return Value : void
    void setAuthority(int authority);
    
    // Function     : void getGroupName()
    // Description  : 유저의 소속 그룹 이름을 반환합니다.
    // Parameters   : void
    // Return Value : string 유저의 소속 그룹이름
    std::string getGroupName();
    
	// Function     : void setGroupName(string groupName)
	// Description  : 유저의 소속 그룹 이름을 지정합니다.
	// Parameters   : string groupName 지정할려는 그룹 이름
	// Return Value : void
    void setGroupName(std::string groupName);
    
protected:
    
    // 생성자
    GroupMember(std::string userID);
    
    //유저 어서리티 (회원0, 그룹 회원1, 그룹 장2)
    int authority;
    
    //유저가 가입해 있는 그룹 이름
    std::string groupName;
};
