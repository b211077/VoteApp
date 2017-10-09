//
//  Boundary.cpp
//  Vote
//
//  Created by San on 2017. 6. 20..
//  Copyright © 2017년 Hongik Univ. All rights reserved.
//

#include "Boundary.h"

#include <sstream>
#include <stdlib.h>
#if __APPLE__
#include <unistd.h>
#else
#include <windows.h>
#include <time.h>
#endif

using namespace std;

void Boundary::showMessage(string message) {
    cout << message.c_str() << endl;
}

// 문자열을 입력받습니다.
const string Boundary::inputString(string message, string alert) {
    string result = "";
    while (true) {
        if (!message.empty()) {
            cout << "* " << message.c_str() << " : ";
        }
        getline(cin, result);
        if (!result.empty()) {
            return result;
        }
        if (alert.empty()) {
            alert = "앗! 빈 문자열입니다. 다시 입력해주세요.";
        }
        cout << alert.c_str() << endl;
    }
    return result;
}

// 숫자를 입력받습니다.
const int Boundary::inputInteger(string message, string alert) {
    int result;
    string input = "";
    while (true) {
        if (!message.empty()) {
            cout << "* " << message.c_str() << " : ";
        }
        getline(cin, input);
        stringstream stream(input);
        if (stream >> result) {
            return result;
        }
        if (alert.empty()) {
            alert = "앗! 숫자를 입력해주세요.";
        }
        cout << alert.c_str() << endl;
    }
    return result;
}

// 불리언을 입력받습니다.
const bool Boundary::inputBool(string message, string alert) {
    string input = "";
    while (true) {
        if (!message.empty()) {
            cout << "* " << message.c_str() << " (Y/N) : ";
        }
        getline(cin, input);
        if (input == "Y" || input == "y") {
            return true;
        } else if (input == "N"  || input == "n") {
            return false;
        }
        if (alert.empty()) {
            alert = "앗! Y 또는 N을 입력해주세요.";
        }
        cout << alert.c_str() << endl;
    }
    return false;
}

void Boundary::clearScreen() {
#if __APPLE__
    cout << string(100, '\n');
#else
    system("cls");
#endif
}

void Boundary::freeze(int seconds) {
#if __APPLE__
    sleep(seconds);
#else
    Sleep(seconds*1000);
#endif
}
