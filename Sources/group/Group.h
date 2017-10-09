#pragma once
// Class        : Group
// Description  : 그룹 데이터를 갖는 entity class
// Created      : 2017/6/19 18:00
// Author       : 주민범
// Mail         : meantiger91@gmail.com

#include <iostream>
#include <list>
#include <vector>
#include "GroupMember.h"

class Vote;

class Group {

public:

	// Function     : Group * create(string name)
	// Description  : 새 그룹 객체를 생성합니다.
	// Parameters   : string name 새그룹을 생성할 그룹 이름입니다.
	// Return Value : Group * 새로운 그룹 객체를 반환합니다.
    static Group * create(std::string name);
    
	// Function     : void setName(string groupName)
	// Description  : 그룹의 이름을 설정합니다.
	// Parameters   : string groupName 그룹 이름이 될 groupName 입니다.
	// Return Value : void
	void setName(std::string groupName);

	// Function     : string getName()
	// Description  : 그룹의 이름을 반환합니다.
	// Parameters   : void
	// Return Value : string 그룹의 이름을 반환합니다.
	std::string getName();
    
    // Function     : void addVote(Vote * vote)
    // Description  : 그룹에 새 투표를 추가합니다.
    // Parameters   : Vote * vote 새로 추가할 투표 객체입니다.
    // Return Value : void
    void addVote(Vote * vote);
    
    // 투표를 삭제합니다.
    bool removeVote(Vote * vote);
    
    // 그룹 내 유저 리스트
    std::list<GroupMember *> members;
    
    // 전체 투표 목록
    std::list<Vote *> votes;
    
private:
    // 생성자
    Group(std::string name);
    
    //그룹 이름
    std::string groupName;
};
