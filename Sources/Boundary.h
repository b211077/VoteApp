// Class        : Boundary
// Description  : UI 클래스에서 사용되는 base class
// Created      : 2017/6/16 21:00
// Author       : 허산
// Mail         : sanheo@me.com

#pragma once

#include <iostream>

class Boundary {
public:
    
    // 메시지를 출력합니다.
    static void showMessage(std::string message);
    
    // 문자열을 입력받습니다.
    static const std::string inputString(std::string message,
                                         std::string alert = "");
    
    // 숫자를 입력받습니다.
    static const int inputInteger(std::string message,
                                  std::string alert = "");
    
    // 불리언을 입력받습니다.
    static const bool inputBool(std::string message,
                                std::string alert = "");
    
    // 화면을 삭제합니다.
    static void clearScreen();
    
    // 주어진 시간동안 화면을 멈춥니다.
    static void freeze(int seconds = 1);
};
