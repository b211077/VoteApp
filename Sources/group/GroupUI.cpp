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
#include <sstream>
#include "../user/Session.h"
#include "GroupUI.h"
#include "GroupControl.h"

using namespace std;

// 존재 하는 모든 그룹 리스트를 출력합니다.
void GroupUI::showGroupList() {
    clearScreen();
    const list<string> groupNames = GroupControl::getAllGroupNames();
	if (groupNames.empty()) {
        showMessage("생성된 그룹이 존재하지 않습니다.");
    } else {
        for (auto iter = groupNames.begin(); iter != groupNames.end(); ++iter)
            cout << *iter << endl;
    }
    freeze(2);
}

//가입되어 있는 그룹의 정보를 출력합니다.
void GroupUI::showGroupInfo() {
    clearScreen();
    GroupMember * user = GroupControl::getCurrentUser();
	if (user == nullptr || user->getAuthority() == 0) {
        showMessage("속해있는 그룹이 없습니다.");
        
	} else {
        Group * group = GroupControl::getCurrentGroup();
        if (group == nullptr) {
            showMessage("그룹이 없습니다.");
            freeze(1);
            return;
        }
        cout << "가입 중인 그룹 : " << group->getName() << endl;
        cout << "그룹 멤버 : " << endl;
        for (auto iter = group->members.begin(); iter != group->members.end(); ++iter)
            cout << (*iter)->getUserID() << endl;
    }
    freeze(2);
}

//그룹 가입 요청
void GroupUI::requestJoinGroup() {
    clearScreen();
    auto session = Session::getInstance();
    User *user = session->getCurrentUser();
    if (user == nullptr) {
        showMessage("로그인이 필요합니다.");
        freeze(1);
        return;
    }
    
    GroupMember * groupMember = dynamic_cast<GroupMember *>(user);
    if (groupMember != nullptr && groupMember->getAuthority() > 0) {
        showMessage("이미 그룹에 가입되어 있습니다.");
        
    } else {
        string groupName = inputString("가입할 그룹명을 입력하세요");
        if (GroupControl::joinGroup(groupName)) {
            cout << groupName << " 그룹에 가입되었습니다." << endl;
        } else {
            cout << groupName << " 그룹에 가입할 수 없습니다." << endl;
        }
    }
    freeze(1);
}

// 그룹 생성 요청
void GroupUI::requestCreateGroup() {
    clearScreen();
    GroupMember * user = GroupControl::getCurrentUser();
    if (user != nullptr && user->getAuthority() > 0) {
        showMessage("이미 그룹에 가입되어 있습니다.");
    } else {
        string groupName = inputString("생성할 그룹명을 입력하세요");
        
        // TODO: 그룹명 중복 체크
        
        if (GroupControl::createGroup(groupName)) {
            showMessage("그룹을 생성했습니다.");
        } else {
            showMessage("그룹을 생성할 수 없습니다.");
        }
    }
    freeze(1);
}

//그룹 삭제 요청
void GroupUI::requestDeleteGroup() {
    clearScreen();
    GroupMember * user = GroupControl::getCurrentUser();
    if (user == nullptr || user->getAuthority() == 0) {
        showMessage("그룹에 속해있지 않습니다");
        
    } else if (user->getAuthority() != 2) {
        showMessage("그룹 삭제는 그룹장만 가능합니다.");
        
    } else {
        if (GroupControl::deleteGroup()) {
            showMessage("그룹이 삭제되었습니다.");
        } else {
            showMessage("그룹을 삭제할 수 없습니다.");
        }
    }
    freeze(1);
}

//그룹 탈퇴 요청
void GroupUI::requestWithdrawGroup() {
    clearScreen();
    GroupMember * user = GroupControl::getCurrentUser();
    if (user == nullptr || user->getAuthority() == 0) {
        showMessage("그룹에 속해있지 않습니다");
        
    } else if (user->getAuthority() == 2) {
        showMessage("그룹장은 그룹에서 탈퇴가 불가능 합니다.");
        
    } else {
        if (GroupControl::withdrawGroup()) {
            showMessage("그룹에서 탈퇴했습니다.");
        } else {
            showMessage("그룹에서 탈퇴할 수 없습니다.");
        }
	}
    freeze(1);
}
