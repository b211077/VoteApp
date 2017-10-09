#pragma once
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

#include "Group.h"
#include "GroupMember.h"
#include "../Boundary.h"

class GroupUI : public Boundary {
    
public:
   
    // Function     : void showGroupList
    // Description  : Group의 전체 리스트를 보여줍니다.
    // Parameters   : none
    // Return Value : void
    static void showGroupList();
    
    // Function     : void showGroupInfo
    // Description  : Group의 정보를 보여줍니다.
    // Parameters   : none
    // Return Value : void
    static void showGroupInfo();
    

    // Function     : void requestJoinGroup
    // Description  : 그룹에 가입을 요청합니다.
    // Parameters   : void
    // Return Value : void
    static void requestJoinGroup();
    

    // Function     : void requestCreateGroup
    // Description  : 그룹 생성을 요청합니다.
    // Parameters   : void
    // Return Value : void
    static void requestCreateGroup();
    

    // Function     : void requestDeleteGroup
    // Description  : 해당 groupName의 그룹 삭제를 요청합니다.
    // Parameters   : void
    // Return Value : void
    static void requestDeleteGroup();
    

    // Function     : void requestWithdrawGroup
    // Description  : 해당 groupName의 그룹에서 탈퇴를 요청합니다.
    // Parameters   : void
    // Return Value : void
    static void requestWithdrawGroup();
    
};
