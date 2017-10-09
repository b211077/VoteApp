#include <iostream>
#include<sstream>
#include "VoteUI.h"
#include "Vote.h"
#include "VoteControl.h"
#include "../user/Session.h"
#include "../group/GroupMember.h"
#include "../group/GroupControl.h"
#include "../data/DataManager.h"
#include "../data/Datetime.h"

using namespace std;

// 투표제안 과정을 시작한다.
void VoteUI::requestNewVote() {
    
    clearScreen();
    
    // 그룹회원인지 확인하기
    GroupMember * groupMember = GroupControl::getCurrentUser();
    if (groupMember == nullptr || groupMember->getAuthority() == 0) {
        if (Session::getInstance()->getCurrentUser() == nullptr) {
            showMessage("로그인이 필요합니다.");
            freeze(1);
            return;
        }
        showMessage("그룹회원이 아닙니다.");
        freeze(1);
        return;
    }
    
    showMessage("투표제안 과정을 시작합니다.");
    
    string title = inputString("투표 주제를 입력하세요");
    string contents = inputString("투표 항목을 입력하세요");
    string startDate, finishDate;
    string startTime, finishTime;
    
    while (true) {
        startDate = inputString("투표 시작 날짜를 입력하세요 (예: 2017년 1월 2일 => 170102)");
        if (Datetime::isValidDate(startDate)) break;
        showMessage("잘못된 날짜입니다. 다시 시도해주세요.");
    }
    
    while (true) {
        startTime = inputString("투표 시작 시각을 입력하세요 (예: 14시 30분 00초 => 143000)");
        if (Datetime::isValidTime(startTime)) break;
        showMessage("잘못된 시간입니다. 다시 시도해주세요.");
    }
    
    while (true) {
        finishDate = inputString("투표 종료 날짜를 입력하세요 (예: 2017년 3월 4일 => 170304)");
        if (Datetime::isValidDate(finishDate)) break;
        showMessage("잘못된 날짜입니다. 다시 시도해주세요.");
    }
    
    while (true) {
        finishTime = inputString("투표 종료 시각을 입력하세요 (예: 14시 30분 00초 => 143000)");
        if (Datetime::isValidTime(finishTime)) break;
        showMessage("잘못된 시간입니다. 다시 시도해주세요.");
    }
    
    Datetime start = Datetime(startDate, startTime);
    Datetime finish = Datetime(finishDate, finishTime);
    
    if (VoteControl::addNewVote(title, contents, start, finish)) {
        showMessage("새 투표를 등록했습니다.");
    } else {
        showMessage("투표를 제안할 수 없습니다.");
    }
    freeze(1);
}

// 현재 진행중인 투표 리스트 조회 과정을 시작한다.
void VoteUI::showOpenVoteList() {
    showVoteList(1);
}

// 종료된 투표 리스트 조회 과정을 시작한다.
void VoteUI::showClosedVoteList() {
    showVoteList(2);
}

// 진행예정인 투표 리스트 조회 과정을 시작한다.
void VoteUI::showUpcomingVoteList() {
    showVoteList(3);
}

// 투표 목록을 출력한다.
void VoteUI::showVoteList(int listNum) {
    string listTitle;
    switch (listNum) {
        case 1:
            listTitle = "현재 진행중인 투표";
            break;
        case 2:
            listTitle = "종료된 투표";
            break;
        case 3:
            listTitle = "진행 예정인 투표";
            break;
        default:
            return;
    }
    
    clearScreen();
    cout << "----- " << listTitle << " 목록 -----" << endl;
    const vector<Vote *> votes = VoteControl::getVoteList(listNum);
    if (votes.empty()) {
        cout << listTitle << "가 없습니다." << endl;
        freeze(1);
        return;
    }
    
    int i=1;
    for (auto iter = votes.begin(); iter != votes.end(); ++iter) {
        cout << i << ". " << (*iter)->title << endl;
        i++;
    }
    
    if (inputBool("투표의 상세정보를 확인하시겠습니까?")) {
        int select;
        while (true) {
            select = inputInteger("원하는 투표의 번호를 입력하세요.");
            if (select < i) {
                break;
            } else {
                showMessage("잘못된 입력입니다.");
            }
        }
        Vote * vote = votes[select-1];
        showVoteDetail(vote);
    }
}

// 투표의 상세정보를 출력한다.
void VoteUI::showVoteDetail(Vote * vote) {
    if (vote == nullptr) return;
    
    clearScreen();
    
    // 투표 상세정보 출력
    cout << "투표 주제 : " << vote->title << endl;
    cout << "투표 항목 : " << vote->contents << endl;
    cout << "시작 시각 : " << vote->start.getDescription() << endl;
    cout << "종료 시각 : " << vote->finish.getDescription() << endl;
    cout << endl << "<현재 투표진행 결과>" << endl;
    cout << "찬성자 수 : " << vote->agree.size() << endl;
    cout << "반대자 수 : " << vote->disagree.size() << endl << endl;
    
    freeze(1);
    
    // 투표 진행/종료여부 판단
    Datetime now = DataManager::getInstance()->getCurrentTime();
    OpenVote * open = nullptr;
    ClosedVote * closed = nullptr;
    if (vote->start <= now && now < vote->finish) {
        open = dynamic_cast<OpenVote*>(vote);
    } else if (now >= vote->finish) {
        closed = dynamic_cast<ClosedVote*>(vote);
    }
    
    if (open != nullptr) {
        cout << "투표 종료까지 " << open->getRemainTime() << " 남았습니다." << endl;
        if (inputBool("투표에 참여하시겠습니까?")) {
            // 투표 참여
            requestApplyVote(open);
        }
    } else if (closed != nullptr) {
        GroupMember * groupMember = GroupControl::getCurrentUser();
        if (groupMember->getAuthority() == 2) {
            if (inputBool("종료된 투표를 삭제하시겠습니까?")) {
                // 투표 삭제
                VoteControl::deleteVote(closed);
            }
        }
    } else {
        freeze(5);
    }
}

// 투표에 참여한다.
void VoteUI::requestApplyVote(OpenVote *vote) {
    if (vote == nullptr) return;
    clearScreen();
    cout << "투표 주제 : " << vote->title << endl;
    cout << "투표 항목 : " << vote->contents << endl << endl;
    
    bool agree = inputBool("찬성하십니까?");
    if (VoteControl::applyVote(vote, agree)) {
        showMessage("투표에 성공적으로 참여했습니다.");
    } else {
        showMessage("이미 참여한 투표입니다.");
    }
    freeze(2);
}
