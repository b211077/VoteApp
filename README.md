# 소프트웨어공학 프로젝트 - 투표 시스템 #

2017년 1학기 소프트웨어공학 프로젝트 4차 과제 구현을 위한 코드 저장소입니다.


## 코딩 규칙 ##

* 소스코드가 포함된 모든 파일은 파일이름 및 내용에 대한 정보를 제공하는 소개 주석으로 문서화되어야 합니다.
* 모든 클래스과 함수 앞에 간단한 설명을 주석으로 적어야 합니다.
* 주석은 // 만 사용합니다.


### 예시: 클래스 주석 규칙 ###

```
 // Class : Test
 // Description: This is a test class. 
 //  ……………………………………….
 //  ……………………………………….
 // Created: 2007/5/10 12:00 pm
 // Author: Gildong Hong
 // mail: gdhong@cs.hongik.ac.kr
 //
 // Revsions : 
 //   1. When & Who : 2007/05/15 13:12 pm by Ji-sung Park
 //      What : added bFlag, 
 //            modified calCosts
 //              …..
 //   2. ……….       
 // 
 // 
```


### 예시: 함수 주석 규칙 ###

```
 // Function : int calCosts(int prevCost, int addedCost)
 // Description: This is a function that calculates the total costs by … 
 //  ……………………………………….
 //  ……………………………………….
 // Parameters :   int prevCost – the previous cost
 //               int added Cost – newly added cost
 // Return Value :  total cost value
 //
 // Created: 2007/5/10 12:00 pm
 // Author: Gildong Hong
 // 
 // Revsions : 
 //   1. When & Who : 2007/05/16 13:12 pm by Ji-sung Park
 //      What : added other factors when calculating costs…
 //              …..
 //   2. ……….       
 // 
 //
```

## 이름 지정 규칙 ##

* 변수, 상수 및 함수의 이름은 소문자로 시작해야 합니다.
* 추상 데이터 유형 (클래스), 구조체, typedef 및 열거형의 이름은 대문자로 시작해야 합니다.
* 하나 이상의 단어로 구성된 이름에서 단어는 함께 쓰여지고 첫 번째 단어 다음에 나오는 단어는 대문자로 시작됩니다.
* 하나 또는 두 개의 밑줄 ( _ 또는 __ )로 시작하는 식별자를 사용하지 마십시오.

### 예시 ###

* 이름의 선택

```
int groupID;    // grpID 대신
int nameLength; // namLn 대신
PrinterStatus resetPrinter; // rstprt 대신
```

* 모호한 이름

```
void termProcess (); // 프로세스 또는 터미널 프로세스를 종료 하시겠습니까?
```

* 숫자가 있는 이름은 찾기 어려운 오류를 유발할 수 있습니다.

```
int I0 = 13; // 숫자가있는 이름은
int IO = I0; // 읽기가 어렵습니다.
```


## 클래스 ##

* 멤버함수를 클래스 정의에서 구현하지 마십시오.
* 클래스에서 public 또는 protected 멤버의 데이터를 지정하지 마십시오.


### 예시 ###

```
#!c++
// 이렇게 작성하지 말고:
class String {
  public:
  int length() const // 안됨 !!
  {
    return len;
  }
  // ...
  private:
  int len;
};
 
// 이렇게 하시오:
class String {
  public:
  int length() const;
  // ...
  private:
  int len;
  };
```