#include <iostream>
#include <ctime>
#include <cmath>
#include "Vote.h"
#include "../data/DataManager.h"
#pragma warning(disable : 4996)

using namespace std;

Vote::Vote()
:voteID("")
,title("")
,contents("")
,start("000000")
,finish("000000")
,agree()
,disagree()
{}

Vote::~Vote()
{}

Vote * Vote::create() {
    Vote * vote = new Vote();
    return vote;
}

void Vote::setVoteInfo(string title, string contents, Datetime start, Datetime finish) {
    
    this->title = title;
    this->contents = contents;
    this->start = start;
    this->finish = finish;
    
}

bool Vote::applied(string userID) {
    return (agree.find(userID) != agree.end() ||
            disagree.find(userID) != disagree.end());
}

OpenVote::OpenVote()
:Vote()
{}

OpenVote::~OpenVote()
{}

// 진행중인 투표 객체를 생성한다.
OpenVote * OpenVote::create(Vote *vote) {
    OpenVote * ret = new OpenVote();
    ret->voteID = vote->voteID;
    ret->title = vote->title;
    ret->contents = vote->contents;
    ret->start = vote->start;
    ret->finish = vote->finish;
    return ret;
}

bool OpenVote::applyVote(string userID, bool agree) {
    // 이미 참여한 투표인지 확인
    if (this->applied(userID)) {
        return false;
    }
    
    if (agree)
        this->agree.insert(userID);
    else
        this->disagree.insert(userID);
    return true;
}

string OpenVote::getRemainTime() {
    Datetime now = DataManager::getInstance()->getCurrentTime();
    int seconds = finish - now;
    float days = floor(seconds/(60*60*24));
    float hours = floor((seconds/(60*60))%24);
    float minutes = int(floor(seconds/60))%60;
    
    char buffer[30];
    sprintf(buffer, "%.0f일 %.0f시간 %.0f분", days, hours, minutes);
    return string(buffer);
}

ClosedVote::ClosedVote()
:Vote()
{}

ClosedVote::~ClosedVote()
{}

// 진행중인 투표 객체를 생성한다.
ClosedVote * ClosedVote::create(Vote *vote) {
    ClosedVote * ret = new ClosedVote();
    ret->voteID = vote->voteID;
    ret->title = vote->title;
    ret->contents = vote->contents;
    ret->start = vote->start;
    ret->finish = vote->finish;
    return ret;
}
