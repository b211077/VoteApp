// Class        : Datetime
// Description  : 문자열로 주어진 날짜 및 시각 정보를 갖는 구조체
// Created      : 2017/6/20 20:00
// Author       : 허산
// Mail         : sanheo@me.com

#include "Datetime.h"
#ifndef __APPLE__
#include "timefunction.h"
#pragma warning(disable : 4996)
#endif
#include <time.h>

using namespace std;


Datetime::Datetime(const string& date)
:date(date)
,time("000000") {
    update();
}

Datetime::Datetime(const string& date, const string& time)
:date(date)
,time(time) {
    update();
}

// 날짜를 설정합니다.
bool Datetime::setDate(const string& value) {
    date = value;
    update();
    return isValidDate();
}

// 시간을 설정합니다.
bool Datetime::setTime(const string& value) {
    time = value;
    update();
    return isValidTime();
}

// 날짜를 반환합니다.
string Datetime::getDate() {
    return date;
}

// 시각을 반환합니다.
string Datetime::getTime() {
    return time;
}

// 날짜와 시각을 문자열로 반환합니다.
string Datetime::getDescription() {
    if (!isValidDate()) return "유효하지 않은 날짜";
    string result = date.substr(0, 2)+"년 ";
    result += date.substr(2, 2)+"월 ";
    result += date.substr(4)+"일";
    if (isValidTime()) {
        result += " ";
        result += time.substr(0, 2)+"시 ";
        result += time.substr(2, 2)+"분 ";
        result += time.substr(4)+"초";
    }
    return result;
}

// 날짜와 시간값이 유효한지 확인합니다.
bool Datetime::isValid() {
    return (isValidDate() && isValidTime());
}

// 날짜가 유효한지 여부
bool Datetime::isValidDate() {
    return validDate;
}

// 시각이 유효한지 여부
bool Datetime::isValidTime() {
    return validTime;
}

// 파라미터의 날짜가 유효한지 확인합니다.
bool Datetime::isValidDate(const string& value) {
    struct tm date;
    return (strptime(value.c_str(), "%y%m%d", &date));
}


// 파라미터의 시각이 유효한지 확인합니다.
bool Datetime::isValidTime(const string& value) {
    struct tm time;
    return (strptime(value.c_str(), "%H%M%S", &time));
}

// 같은 날짜인지 확인하는 연산자
bool Datetime::operator==(const Datetime &other) {
    return (date == other.date && time == other.time);
}

// 상대값보다 미래이거나 같은 날짜인지 확인하는 연산자
bool Datetime::operator<(const Datetime &other) {
    if (date == other.date)
        return (time < other.time);
    else
        return (date < other.date);
}

// 상대값보다 미래 날짜인지 확인하는 연산자
bool Datetime::operator>(const Datetime &other) {
    if (date == other.date)
        return (time > other.time);
    else
        return (date > other.date);
}

// 상대값보다 과거이거나 같은 날짜인지 확인하는 연산자
bool Datetime::operator<=(const Datetime &other) {
    return (*this<other || *this==other);
}

// 상대값보다 미래이거나 같은 날짜인지 확인하는 연산자
bool Datetime::operator>=(const Datetime &other) {
    return (*this>other || *this==other);
}

// 두 시각의 차이값을 반환합니다.
int Datetime::operator-(Datetime &other) {
    long left = static_cast<long>(mktime(&datetime));
    long right = static_cast<long>(mktime(&other.datetime));
    return static_cast<int>(left-right);
}

// 내부 시각값을 갱신합니다.
void Datetime::update() {
    validDate = isValidDate(date);
    validTime = isValidTime(time);
    if (!validDate) return;
    if (validTime) {
        string dateString = date+time;
        strptime(dateString.c_str(), "%y%m%d%H%M%S", &datetime);
    } else {
        string dateString = date;
        strptime(dateString.c_str(), "%y%m%d", &datetime);
    }
}
