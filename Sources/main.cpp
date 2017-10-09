//
//  main.cpp
//  Vote
//
//  Created by San on 2017. 6. 16..
//  Copyright © 2017년 Hongik Univ. All rights reserved.
//

#include <iostream>
#include "MenuUI.h"

using namespace std;

// 메인 루프
int main(int argc, const char * argv[]) {
    
    MenuUI * menuUI = new MenuUI();
    
    int mainMenu = 0;
    int subMenu = 0;
    while (true) {
        menuUI->showMenu(mainMenu);
        (mainMenu > 0 ? subMenu : mainMenu) = menuUI->selectMenu();
        if (menuUI->executeMenu(mainMenu, subMenu)) {
            mainMenu = 0;
            subMenu = 0;
        }
    }
    
    return 0;
}
