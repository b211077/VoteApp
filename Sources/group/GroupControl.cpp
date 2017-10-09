// Class        : GroupControl
// Description  : 그룹의 control class
// Created      : 2017/6/16 22:00
// Author       : 주민범
// Mail         : meantiger91@gmail.com

#include "GroupControl.h"
#include "../data/DataManager.h"
#include "../user/Session.h"

using namespace std;

// 모든 그룹명 목록을 반환합니다.
const list<string> GroupControl::getAllGroupNames() {
    auto data = DataManager::getInstance();
    list<string> groupNames = list<string>();
    auto groups = data->getAllGroups();
    for (auto iter = groups.begin(); iter != groups.end(); ++iter) {
        groupNames.push_back(iter->second->getName());
    }
    return groupNames;
}

// 현재 사용자의 그룹회원 객체를 반환합니다.
GroupMember * GroupControl::getCurrentUser() {
    User *user = Session::getInstance()->getCurrentUser();
    if (user == nullptr) {
        // 로그인 되지 않음.
        return nullptr;
    }
    GroupMember * groupMember = dynamic_cast<GroupMember *>(user);
    if (groupMember == NULL || groupMember == nullptr) {
        // 그룹회원이 아님.
        return nullptr;
    }
    return groupMember;
}

// 현재 사용자가 가입한 그룹을 반환합니다.
Group * GroupControl::getCurrentGroup() {
    GroupMember * user = GroupControl::getCurrentUser();
    if (user == nullptr) {
        return nullptr;
    }
    string groupName = user->getGroupName();
    Group * group = DataManager::getInstance()->getGroup(groupName);
    return group;
}

// 그룹명에 해당하는 그룹에 가입합니다.
bool GroupControl::joinGroup(std::string groupName) {
    auto session = Session::getInstance();
    User *user = session->getCurrentUser();
    if (user == nullptr) { return false; }
    
    auto data = DataManager::getInstance();
    Group * group = data->getGroup(groupName);
    if (group == nullptr) {
        return false;
    }
    
    GroupMember * groupMember = dynamic_cast<GroupMember *>(user);
    
    // 그룹회원이 아닌 경우, 그룹회원으로 승격 (세션 및 데이터에 업데이트)
    if (groupMember == NULL || groupMember == nullptr) {
        groupMember = GroupMember::create(user);
        data->updateUser(groupMember);
        session->activateUser(groupMember);
    }
    
    // 그룹 가입
    if (groupMember->getAuthority() == 0) {
        group->members.push_back(groupMember);
        groupMember->setAuthority(1);
        groupMember->setGroupName(groupName);
        return true;
    }
    return false;
}

// 새 그룹을 생성합니다.
bool GroupControl::createGroup(std::string groupName) {
    
    auto session = Session::getInstance();
    auto data = DataManager::getInstance();
    User *user = session->getCurrentUser();
    
    GroupMember * groupMember = dynamic_cast<GroupMember *>(user);
    if (groupMember == NULL || groupMember == nullptr) {
        // 그룹회원이 아닌 경우, 그룹회원으로 승격 (세션 및 데이터에 업데이트)
        groupMember = GroupMember::create(user);
        data->updateUser(groupMember);
        session->activateUser(groupMember);
    }
    
    // 새 그룹 생성 및 저장
    if (groupMember->getAuthority() == 0) {
        Group * newGroup = Group::create(groupName);
        newGroup->members.push_back(groupMember);
        groupMember->setAuthority(2);
        groupMember->setGroupName(groupName);
        data->addGroup(newGroup);
        return true;
    } else {
        return false;
    }
}

// 현재 사용자가 가입한 그룹을 삭제합니다.
bool GroupControl::deleteGroup() {
    GroupMember * user = GroupControl::getCurrentUser();
    if (user == nullptr) { return false; }
    
    string groupName = user->getGroupName();
    auto data = DataManager::getInstance();
    Group * group = data->getGroup(groupName);
    if (group != nullptr && data->deleteGroup(group)) {
        group = nullptr;
        user->setGroupName("");
        user->setAuthority(0);
        return true;
    }
    return false;
}

// 현재 사용자가 가입한 그룹에서 탈퇴합니다.
bool GroupControl::withdrawGroup() {
    GroupMember * user = GroupControl::getCurrentUser();
    if (user == nullptr || user->getAuthority() != 1) {
        return false;
    }
    
    string groupName = user->getGroupName();
    Group * group = DataManager::getInstance()->getGroup(groupName);
    if (group) {
        group->members.remove(user);
    }
    user->setAuthority(0);
    user->setGroupName("");
    return true;
}
