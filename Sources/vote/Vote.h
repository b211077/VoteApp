// Class        : Vote
// Description  : 투표 시스템의 entity class
// Created      : 2017/6/17 23:00
// Author       : 박성준
// Mail         : sungjun429@daum.net

#pragma once

#include <set>
#include "../data/Datetime.h"

class Vote {
public:
    // 새 투표 객체를 생성한다.
    static Vote* create();
    
    // Function     : void setVoteInfo(string title, string contents, Datetime start, Datetime finish)
    // Description  : 투표 제안 정보를 전달받아 설정한다.
    // Parameters   : title, contents, start, finish
    // Return Value : none
    void setVoteInfo(std::string title, std::string contents, Datetime start, Datetime finish);
    
    // 투표 아이디
    std::string voteID;
    
    // 제목
    std::string title;
    
    // 내용
    std::string contents;
    
    // 시작시각
    Datetime start;
    
    // 종료시각
    Datetime finish;
    
    // 찬성 회원 목록
    std::set<std::string> agree;
    
    // 반대 회원 목록
    std::set<std::string> disagree;
    
    // 사용자 아이디로 투표 참여 여부를 조회한다.
    bool applied(std::string userID);
    
    // 소멸자
    virtual ~Vote();
    
protected:
    // 생성자
    Vote();
};

// Class        : OpenVote
// Description  : 투표 시스템의 entity class
// Created      : 2017/6/18 18:00
// Author       : 박성준
class OpenVote : public Vote {
public:
    // 진행중인 투표 객체를 생성한다.
    static OpenVote* create(Vote* vote);
    
    // Function     : void applyVote(std::string userID, bool agree)
    // Description  : 투표에 찬성/반대표를 기록한다.
    // Parameters   : userID, agree
    // Return Value : bool 투표 성공여부
    bool applyVote(std::string userID, bool agree);
    
    // Function     : std::string getRemainTime()
    // Description  : 진행중인 투표의 남은 시간을 반환한다.
    // Parameters   : none
    // Return Value : string 남은 시간의 문자열
    std::string getRemainTime();
    
    // 소멸자
    virtual ~OpenVote();
    
private:
    // 생성자
    OpenVote();
};


// Class        : ClosedVote
// Description  : 투표 시스템의 entity class
// Created      : 2017/6/18 18:00
// Author       : 박성준
// Mail         : sungjun429@daum.net
class ClosedVote : public Vote {
public:
    // 종료된 투표 객체를 생성한다.
    static ClosedVote* create(Vote* vote);
    
    // 소멸자
    virtual ~ClosedVote();
    
private:
    // 생성자
    ClosedVote();
};
