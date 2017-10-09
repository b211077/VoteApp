// Class        : MainUI
// Description  : 프로그램의 메인 UI
// Created      : 2017/6/20 16:00
// Author       : 허산
// Mail         : sanheo@me.com

#pragma once

#include "Boundary.h"
#include <list>
#include <map>
#include <sstream>

class MenuUI : public Boundary {
public:
    // 생성자
    MenuUI();
    
    void showMenu(int menu);
    
    bool executeMenu(int mainMenu, int subMenu);
    
    int selectMenu();
    
    int maxMenu;
    
    void changeTime();
};
