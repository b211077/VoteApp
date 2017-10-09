// Class        : GroupControl
// Description  : 그룹의 control class
// Created      : 2017/6/16 22:00
// Author       : 주민범
// Mail         : meantiger91@gmail.com

#pragma once

#include <iostream>
#include <list>
#include "Group.h"
#include "GroupMember.h"

class GroupControl {
public:
	// Function     : list getAllGroupNames()
	// Description  : 현재 존재하는 모든 그룹 이름을 반환합니다.
	// Parameters   : void
	// Return Value : list 모든 그룹 이름을 가진 리스트.
    static const std::list<std::string> getAllGroupNames();
    
    // Function     : GroupMember * getCurrentUser()
    // Description  : 현재 사용자의 그룹회원 객체를 반환합니다.
    // Parameters   : void
    // Return Value : GroupMember * 현재 그룹회원 객체
    static GroupMember * getCurrentUser();
    
    // Function     : Group *getCurrentGroup()
    // Description  : 현재 사용자가 가입한 그룹을 반환합니다.
    // Parameters   : void
    // Return Value : Group * 현재 사용자가 속한 그룹
    static Group * getCurrentGroup();
    
    // Function     : bool joinGroup(string groupName)
    // Description  : 그룹명에 해당하는 그룹에 가입합니다.
    // Parameters   : string groupName 가입하고자 하는 그룹 이름
    // Return Value : bool 가입 성공여부
    static bool joinGroup(std::string groupName);
    
    // Function     : bool createGroup(string groupName)
    // Description  : 새 그룹을 생성합니다.
    // Parameters   : string groupName 만들고자 하는 그룹 이름
    // Return Value : bool 생성 성공여부
    static bool createGroup(std::string groupName);
    
    // Function     : bool deleteGroup()
    // Description  : 현재 사용자가 가입한 그룹을 삭제합니다.
    // Parameters   : void
    // Return Value : bool 삭제 성공여부
    static bool deleteGroup();
    
    // Function     : bool withdrawGroup()
    // Description  : 현재 사용자가 가입한 그룹에서 탈퇴합니다.
    // Parameters   : void
    // Return Value : bool 탈퇴 성공 여부 
    static bool withdrawGroup();
};
