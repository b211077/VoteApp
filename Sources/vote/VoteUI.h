// Class        : VoteUI
// Description  : 투표 시스템의 boundary class
//                사용자는 UI를 통해 투표제안, 현재 진행중인 투표리스트 조회, 향후 진행 예정인 투표 리스트 조회,
//				  종료된 투표 리스트 조회, 투표하기, 종료된 투표 삭제 기능을 요청할 수 있다.
// Created      : 2017/6/17 23:00
// Author       : 박성준
// Mail         : sungjun429@daum.net

#pragma once

#include "../Boundary.h"

class Vote;
class OpenVote;

class VoteUI : public Boundary{
public:
    // Function     : void requestNewVote()
    // Description  : 투표제안 과정을 시작한다.
    // Parameters   : none
    // Return Value : none
    static void requestNewVote();
    
    // Function     : void showOpenVoteList()
    // Description  : 현재 진행중인 투표 리스트 조회 과정을 시작한다.
    // Parameters   : none
    // Return Value : none
    static void showOpenVoteList();
    
    // Function     : void showClosedVoteList()
    // Description  : 종료된 투표 리스트 조회 과정을 시작한다.
    // Parameters   : none
    // Return Value : none
    static void showClosedVoteList();
    
    // Function     : void showUpcomingVoteList()
    // Description  : 진행예정인 투표 리스트 조회 과정을 시작한다.
    // Parameters   : none
    // Return Value : none
	static void showUpcomingVoteList();
    
    // 투표 목록을 출력한다.
    static void showVoteList(int listNum);
    
    // 투표의 상세정보를 출력한다.
    static void showVoteDetail(Vote * vote);
    
    // 투표에 참여한다.
    static void requestApplyVote(OpenVote * vote);
};


