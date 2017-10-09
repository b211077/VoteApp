//==============================================================================================================
//Boundary Class
//==============================================================================================================
// Class        : GroupUI
// Description  : 투표 시스템의 boundary class
//                사용자는 UI를 통해 그룹 리스트 조회, 그룹 정보 조회, 그룹 가입 요청, 그룹 생성 요청, 그룹 삭제
//				  요청, 그룹 탈퇴 요청 등을 진행 할 수 있다.
// Created      : 2017/6/19 18:00
// Author       : 주민범
// Mail         : meantiger91@gmail.com
//==============================================================================================================

#include <iostream>
#include "Group.h"
#include "../vote/Vote.h"

using namespace std;

Group * Group::create(string name) {
    Group * group = new Group(name);
    return group;
}

Group::Group(string name)
:groupName(name)
,members()
,votes()
{
}


void Group::setName(string groupName)
{
	this->groupName = groupName;
}

string Group::getName()
{
	return this->groupName;
}

// 그룹에 새 투표를 추가합니다.
void Group::addVote(Vote * vote) {
    if (vote == nullptr) {return;}
    votes.push_back(vote);
}

bool Group::removeVote(Vote *vote) {
    for (auto iter = votes.cbegin(); iter != votes.cend(); ++iter) {
        if (*iter == vote) {
            votes.erase(iter);
            delete vote;
            vote = nullptr;
            return true;
        }
    }
    return false;
}
