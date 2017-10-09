// Class        : VoteControl
// Description  : 투표 시스템의 control class
//                투표 등록, 투표 리스트 조회를 수행한다.
// Created      : 2017/6/17 23:00
// Author       : 박성준
// Mail         : sungjun429@daum.net

#pragma once

#include <vector>
#include "Vote.h"

class VoteControl {
public:
    // Function     : void addNewVote(string title, string contents, int startDate, int finishTime)
    // Description  : 투표 제안 정보를 전달받아 투표를 등록한다.
    // Parameters   : title, contents, start, finish
    // Return Value : bool 투표 등록 성공여부
    static bool addNewVote(std::string title, std::string contents, Datetime start, Datetime finish);
    
    // Function     : void VoteList()
    // Description  : 현재 진행중인, 중료된, 진행예정인 투표 리스트 조회를 요청받아 전달한다.
    // Parameters   : none
    // Return Value : none
    static const std::vector<Vote *> getVoteList(int listNum);
    
    
    // 투표를 삭제합니다.
    static bool deleteVote(ClosedVote * vote);
    
    // 투표에 참여합니다.
    static bool applyVote(OpenVote * vote, bool agree);
};
