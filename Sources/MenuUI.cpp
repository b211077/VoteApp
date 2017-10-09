// Class        : MainUI
// Description  : 프로그램의 메인 UI
// Created      : 2017/6/20 16:00
// Author       : 허산
// Mail         : sanheo@me.com


#include "MenuUI.h"
#include "user/Session.h"

#include "user/UserUI.h"
#include "group/GroupUI.h"
#include "vote/VoteUI.h"
#include "data/DataManager.h"
#include "data/Datetime.h"

using namespace std;

MenuUI::MenuUI()
:maxMenu(0)
{
}

// 메뉴를 화면에 출력한다.
void MenuUI::showMenu(int menu) {
    clearScreen();
    switch (menu) {
        case 1:
            cout << "----- 회원가입/탈퇴 -----" << endl;
            cout << "1. 회원가입" << endl;
            cout << "2. 회원탈퇴" << endl;
            cout << "3. 메인으로 돌아가기" << endl;
            maxMenu = 3;
            break;
        case 2:
            cout << "----- 로그인/로그아웃 -----" << endl;
            cout << "1. 로그인" << endl;
            cout << "2. 로그아웃" << endl;
            cout << "3. 메인으로 돌아가기" << endl;
            maxMenu = 3;
            break;
        case 4:
            cout << "----- 투표관리 -----" << endl;
            cout << "1. 현재 진행 중인 투표 리스트" << endl;
            cout << "2. 종료된 투표리스트" << endl;
            cout << "3. 향후 진행 예정인 투표 리스트" << endl;
            cout << "4. 메인으로 돌아가기" << endl;
            maxMenu = 4;
            break;
        case 5:
            cout << "----- 그룹관리 -----" << endl;
            cout << "1. 전체그룹 조회" << endl;
            cout << "2. 그룹 가입" << endl;
            cout << "3. 그룹 생성" << endl;
            cout << "4. 가입그룹 조회" << endl;
            cout << "5. 그룹 탈퇴" << endl;
            cout << "6. 메인으로 돌아가기" << endl;
            maxMenu = 6;
            break;
        default:
            cout << "===== 투표 시스템 =====" << endl;
            User * user = Session::getInstance()->getCurrentUser();
            if (user != nullptr) {
                cout << user->name << "님, 환영합니다!" << endl;
            }
            cout << "1. 회원가입/탈퇴" << endl;
            cout << "2. 로그인/로그아웃" << endl;
            cout << "3. 투표제안" << endl;
            cout << "4. 투표관리" << endl;
            cout << "5. 그룹관리" << endl;
            cout << "6. 현재시간 설정" << endl;
            cout << "7. Session 변경/선택" << endl;
            cout << "8. 종료" << endl;
            maxMenu = 8;
            break;
    }
}


// 입력된 메뉴에 해당하는 명령을 실행한다.
// 실행이 완료되면 true를 반환하여, 메뉴선택을 초기화한다.
bool MenuUI::executeMenu(int mainMenu, int subMenu) {
    switch (mainMenu) {
        case 1: { // 회원가입/탈퇴
            switch (subMenu) {
                case 1:
                    // 회원가입
                    UserUI::requestSignup();
                    return true;
                case 2:
                    // 회원탈퇴
                    UserUI::requestWithdraw();
                    return true;
                case 3:
                    return true;
                default:
                    break;
            }
            // 서브메뉴 선택이 필요한 경우 false를 반환함
            return false;
        }
        case 2: { // 로그인/로그아웃
            switch (subMenu) {
                case 1:
                    // 로그인
                    UserUI::requestLogin();
                    return true;
                case 2:
                    // 로그아웃
                    UserUI::requestLogout();
                    return true;
                case 3:
                    return true;
                default:
                    break;
            }
            // 서브메뉴 선택이 필요한 경우 false를 반환함
            return false;
        }
        case 3: { // 투표제안
            // 투표제안
            VoteUI::requestNewVote();
            return true;
        }
        case 4: { // 투표관리
            switch (subMenu) {
                case 1:
                    // 현재 진행 중인 투표 리스트
                    VoteUI::showOpenVoteList();
                    return true;
                case 2:
                    // 종료된 투표리스트
                    VoteUI::showClosedVoteList();
                    return true;
                case 3:
                    // 향후 진행 예정인 투표 리스트
                    VoteUI::showUpcomingVoteList();
                    return true;
                case 4:
                    return true;
                default:
                    break;
            }
            // 서브메뉴 선택이 필요한 경우 false를 반환함
            return false;
        }
        case 5: { // 그룹관리
            switch (subMenu) {
                case 1:
                    // 전체그룹 조회
                    GroupUI::showGroupList();
                    return true;
                case 2:
                    // 그룹 가입
                    GroupUI::requestJoinGroup();
                    return true;
                case 3:
                    // 그룹 생성
                    GroupUI::requestCreateGroup();
                    return true;
                case 4:
                    // 가입그룹 조회
                    GroupUI::showGroupInfo();
                    return true;
                case 5:
                    // 그룹 탈퇴
                    GroupUI::requestWithdrawGroup();
                    return true;
                case 6:
                    return true;
                default:
                    break;
            }
            // 서브메뉴 선택이 필요한 경우 false를 반환함
            return false;
        }
        case 6: {
            // 현재시간 설정
            changeTime();
            return true;
        }
        case 7: {
            // Session 선택/변경
            UserUI::requestChangeSession();
            return true;
        }
        case 8: { // 종료
            exit(0);
        }
        default:
            break;
    }
    // 선택에 해당하는 메뉴가 없는 경우, true를 반환해 선택을 초기화.
    return true;
}

// 사용자가 선택하고 싶은 메뉴를 숫자로 입력받는다.
int MenuUI::selectMenu() {
    int selectedNumber = 0;
    while (true) {
        selectedNumber = inputInteger("원하는 메뉴를 입력해주세요");
        // 유효한 범위의 메뉴번호를 선택했는지 확인한다.
        if (0 < selectedNumber && selectedNumber <= maxMenu)
            break;
        else
            cout << "앗! 표시된 메뉴에 해당하는 숫자를 입력해주세요.";
    }
    return selectedNumber;
}

// 시간 변경
void MenuUI::changeTime() {
    clearScreen();
    
    auto data = DataManager::getInstance();
    Datetime now = data->getCurrentTime();
    cout << "지금은 " << now.getDescription() << " 입니다." << endl;
    
    if (inputBool("시간을 변경하시겠습니까?")) {
        string newTime;
        while (true) {
            newTime = inputString("원하는 시간,분,초를 6자리로 입력해주세요. (예시: 143000)");
            if (Datetime::isValidTime(newTime)) {
                break;
            } else {
                showMessage("잘못된 시간 형식입니다. 다시 시도해주세요.");
            }
        }
        data->changeTime(newTime);
        showMessage("시간이 변경되었습니다.");
        freeze(2);
    }
    
}
