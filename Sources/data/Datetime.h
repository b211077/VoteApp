// Class        : Datetime
// Description  : 문자열로 주어진 날짜 및 시각 정보를 갖는 구조체
// Created      : 2017/6/20 20:00
// Author       : 허산
// Mail         : sanheo@me.com

#pragma once

#include <sstream>

typedef struct Datetime {
    
public:
    
    // 지정된 날짜만으로 초기화
    Datetime(const std::string& date);
    
    // 지정된 날짜와 시각으로 초기화
    Datetime(const std::string& date, const std::string& time);
    
    // 날짜를 설정합니다.
    bool setDate(const std::string& value);
    
    // 시간을 설정합니다.
    bool setTime(const std::string& value);
    
    // 날짜를 반환합니다.
    std::string getDate();
    
    // 시각을 반환합니다.
    std::string getTime();
    
    // 날짜와 시각을 문자열로 반환합니다.
    std::string getDescription();
    
    // 날짜와 시각이 유효한지 확인합니다.
    bool isValid();
    
    // 날짜가 유효한지 확인합니다.
    bool isValidDate();
    
    // 시각이 유효한지 확인합니다.
    bool isValidTime();
    
    // 파라미터의 날짜가 유효한지 확인합니다.
    static bool isValidDate(const std::string& value);
    
    // 파라미터의 시각이 유효한지 확인합니다.
    static bool isValidTime(const std::string& value);
    
    // 같은 날짜인지 확인하는 연산자
    bool operator==(const Datetime &other);
    
    // 상대값보다 과거 날짜인지 확인하는 연산자
    bool operator<(const Datetime &other);
    
    // 상대값보다 미래 날짜인지 확인하는 연산자
    bool operator>(const Datetime &other);
    
    // 상대값보다 과거이거나 같은 날짜인지 확인하는 연산자
    bool operator<=(const Datetime &other);
    
    // 상대값보다 미래이거나 같은 날짜인지 확인하는 연산자
    bool operator>=(const Datetime &other);
    
    // 두 시각의 차이값을 반환합니다.
    int operator-(Datetime &other);
    
protected:
    // 날짜 (YYMMDD)
    std::string date;
    
    // 시각 (HHmmss)
    std::string time;
    
    // 유효한 날짜인지 여부
    bool validDate;
    
    // 유효한 시각인지 여부
    bool validTime;
    
    // 내부적으로 사용되는 시각값
    tm datetime;
    
    // 내부 시각값을 갱신합니다.
    void update();
} Datetime;
