// Class        : GroupMember
// Description  : 그룹 회원의 entity class
// Created      : 2017/6/16 22:00
// Author       : 주민범
// Mail         : meantiger91@gmail.com

#include "GroupMember.h"

using namespace std;

// 사용자의 정보를 복사하여 그룹회원 객체를 생성합니다.
GroupMember * GroupMember::create(User * user) {
    if (user == nullptr) {
        return nullptr;
    }
    GroupMember * groupMember = new GroupMember(user->getUserID());
    groupMember->password = user->password;
    groupMember->name = user->name;
    groupMember->birthday = user->birthday;
    groupMember->address = user->address;
    groupMember->email = user->email;
    return groupMember;
}

GroupMember::GroupMember(string userID)
:User(userID)
,authority(0)
{
}

GroupMember::~GroupMember()
{
}

int GroupMember::getAuthority()
{
    return this->authority;
}

void GroupMember::setAuthority(int authority)
{
    this->authority = authority;
}

void GroupMember::setGroupName(std::string groupName)
{
    this->groupName = groupName;
}

std::string GroupMember::getGroupName()
{
    return this->groupName;
}

