// Class        : DataManager
// Description  : 투표시스템의 데이터를 기록하는 클래스
// Created      : 2017/6/19 19:00
// Author       : 허산
// Mail         : sanheo@me.com

#pragma once

#include <map>
#include "../user/User.h"
#include "../group/Group.h"
#include "Datetime.h"

class DataManager {

public:
    // Function     : DataManager * getInstance()
    // Description  : DataManager 클래스의 싱글턴 인스턴스를 불러옵니다.
    // Parameters   : none
    // Return Value : DataManager instance
    static DataManager* getInstance();


    // 사용자를 추가합니다.
    void addUser(User * user);

    // 사용자를 불러옵니다. 사용자가 없는 경우 nullptr를 반환합니다.
    User * getUser(std::string userID);

    // 사용자를 갱신합니다.
    bool updateUser(User * user);
    
    // 사용자를 삭제합니다.
    void deleteUser(User * user);

    
    // 새 그룹을 추가합니다.
    void addGroup(Group * group);
    
    // 그룹을 불러옵니다. 그룹이 없는 경우 nullptr를 반환합니다.
    Group * getGroup(std::string name);
    
    // 전체 그룹을 불러옵니다.
    const std::map<std::string, Group *> getAllGroups();
    
    // 그룹을 삭제합니다.
    bool deleteGroup(Group * group);
    
    // 현재 시각을 반환합니다.
    Datetime getCurrentTime(bool adjusted = true);
    
    // 현재 시각을 변경합니다.
    bool changeTime(std::string time);
    
private:

    // 생성자
    DataManager();

    // 소멸자
    ~DataManager();

    // 회원가입한 사용자들
    std::map<std::string, User *> users;

    // 전체 그룹 목록
    std::map<std::string, Group *> groups;
    
    // 시간 변경시 차이값
    int timeDifference;
    
};
