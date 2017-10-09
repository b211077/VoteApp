// Class        : DataManager
// Description  : 투표시스템의 데이터를 기록하는 클래스
// Created      : 2017/6/19 19:00
// Author       : 허산
// Mail         : sanheo@me.com

#include "DataManager.h"
#include <ctime>
#include <iomanip>

using namespace std;

static DataManager * instance = nullptr;

DataManager * DataManager::getInstance() {
    if (!instance) {
        instance = new DataManager();
    }
    return instance;
}

DataManager::DataManager()
:users()
,groups()
,timeDifference(0)
{
}

void DataManager::addUser(User *user) {
    users[user->getUserID()] = user;
}

User * DataManager::getUser(string userID) {
    auto iterator = users.find(userID);
    if (iterator == users.end()) {
        return nullptr;
    } else {
        return iterator->second;
    }
}

bool DataManager::updateUser(User *user) {
    if (user == nullptr) { return false; }
    
    string userID = user->getUserID();
    User * oldUser = this->getUser(userID);
    if (oldUser != nullptr) {
        // 같은 아이디의 사용자가 이미 있는 경우
        this->deleteUser(oldUser);
    }
    this->addUser(user);
    return true;
}

void DataManager::deleteUser(User *user) {
    string userID = user->getUserID();
    delete user;
    users.erase(userID);
}


// 새 그룹을 추가합니다.
void DataManager::addGroup(Group * group) {
    groups[group->getName()] = group;
}

// 그룹을 불러옵니다. 그룹이 없는 경우 nullptr를 반환합니다.
Group * DataManager::getGroup(std::string name) {
    auto iterator = groups.find(name);
    if (iterator == groups.end()) {
        return nullptr;
    } else {
        return iterator->second;
    }
}

// 전체 그룹을 불러옵니다.
const std::map<std::string, Group *> DataManager::getAllGroups() {
    return groups;
}

// 그룹을 삭제합니다.
bool DataManager::deleteGroup(Group * group) {
    if (group == nullptr) {return false;}
    
    string groupID = group->getName();
    delete group;
    groups.erase(groupID);
    return true;
}

// 현재 시각을 반환합니다.
Datetime DataManager::getCurrentTime(bool adjusted) {
    
    time_t now = std::time(nullptr);
    if (adjusted) now += timeDifference;
    
#if __APPLE__
    tm * time = std::localtime(&now);
#else
    tm * time = new tm;
    localtime_s(time, &now);
#endif
    
    stringstream stream;
    stream << std::put_time(time, "%y%m%d%H%M%S");
    string datetime = stream.str();
    return Datetime(datetime.substr(0, 6), datetime.substr(6));
}

// 현재 시각을 변경합니다.
bool DataManager::changeTime(string time) {
    Datetime now = getCurrentTime(false);
    Datetime target = Datetime(now.getDate(), time);
    if (target.isValid()) {
        // 실제 시간과 원하는 시간의 초단위 차이를 기록함.
        timeDifference = target - now;
        return true;
    } else {
        return false;
    }
}
