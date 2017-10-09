#include <iostream>
#include <time.h>
#include "VoteControl.h"
#include "../data/DataManager.h"
#include "../group/GroupControl.h"


using namespace std;

// 투표 제안 정보를 전달받아 투표를 등록한다.
bool VoteControl::addNewVote(string title, string contents, Datetime start, Datetime finish) {
    
    auto groupMember = GroupControl::getCurrentUser();
    if (groupMember == nullptr || groupMember->getAuthority() == 0) {
        // 그룹회원이 아님
        return false;
    }
    
    auto data = DataManager::getInstance();
    auto group = data->getGroup(groupMember->getGroupName());
    
    Vote * vote = Vote::create();
	vote->setVoteInfo(title, contents, start, finish);
    group->addVote(vote);
    return true;
}

const vector<Vote *> VoteControl::getVoteList(int listNum) {
    vector<Vote *> result = vector<Vote *>();
    auto groupMember = GroupControl::getCurrentUser();
    if (groupMember == nullptr || groupMember->getAuthority() == 0) {
        // 그룹회원이 아님
        return result;
    }
    
    auto data = DataManager::getInstance();
    auto group = data->getGroup(groupMember->getGroupName());
    if (group == nullptr) {
        // 그룹이 없음
        return result;
    }
    
    Datetime now = data->getCurrentTime();
    for (auto iter = group->votes.begin(); iter != group->votes.end(); ++iter) {
        Vote * vote = *iter;
        if (listNum == 1                // 현재 진행중인 목록
            && vote->start <= now       // 과거에 시작
            && vote->finish > now       // 미래에 종료
            ) {
            result.push_back(vote);
        }
        else if (listNum == 2           // 종료된 목록
                 && vote->finish <= now // 오늘 이전에 종료
                 ) {
            result.push_back(vote);
        }
        else if (listNum == 3           // 진행 예정인 목록
                 && vote->start >= now  // 오늘 이후에 시작
                 ) {
            result.push_back(vote);
        }
    }
    
    // 타입 캐스팅
    for (auto iter = result.cbegin(); iter != result.cend(); ++iter) {
        if (listNum == 1) {
            OpenVote * casted = dynamic_cast<OpenVote*>(*iter);
            if (casted == nullptr) {
                casted = OpenVote::create(*iter);
                group->addVote(casted);
                group->removeVote(*iter);
                result.erase(iter);
                result.push_back(casted);
            }
        } else if (listNum == 2) {
            ClosedVote * casted = dynamic_cast<ClosedVote*>(*iter);
            if (casted == nullptr) {
                casted = ClosedVote::create(*iter);
                group->addVote(casted);
                group->removeVote(*iter);
                result.erase(iter);
                result.push_back(casted);
            }
        }
    }
    
    return result;
}

bool VoteControl::deleteVote(ClosedVote * vote) {
    auto user = GroupControl::getCurrentUser();
    if (user == nullptr || user->getAuthority() != 2) {
        // 그룹장이 아닌 경우 실패
        return false;
    }
    auto data = DataManager::getInstance();
    auto group = data->getGroup(user->getGroupName());
    bool success = group->removeVote(vote);
    return success;
}

bool VoteControl::applyVote(OpenVote * vote, bool agree) {
    auto user = GroupControl::getCurrentUser();
    if (user == nullptr || user->getAuthority() == 0) {
        return false;
    }
    bool success = vote->applyVote(user->getUserID(), agree);
    return success;
}
