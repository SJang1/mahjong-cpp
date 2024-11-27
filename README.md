# (리치)마작의 기초 - 4인 보드게임
마작은 도박이 아닌 **보드게임입니다.**

"건전한 선택, 건강한 미래! 도박에 NO를 외치세요!"  
마작을 도박으로 하지 마세요!

## 정답?
정답은 없습니다. 심지어 이 레포지토리 안에 있는 코드도 정답이 아니며, 아무튼 작동하게 :tm: 상태로 만들어 둔 것으로 저도 다시 만들어야 합니다.

현재 만들어진 코드의 실행 결과를 참고해서 만들어 보시면 되겠습니다.

refactoring 해야 할 내용 산더미고, 경고도 있습니다.

화이팅입니다!!!

## 문제

### 마작에는 아래 종류의 패가 있다.
- `만수패`, `통수패`, `삭수패`라는 숫자 패 3종류, **[각각 1~9까지 있음]()**
- `동패`, `남패`, `서패`, `북패`라는 방향을 가르키는 풍패 4종류
- `백패`, `발패`, `중패` 라고 하는 모양으로 된 삼원패 3종류
[![image](https://github.com/user-attachments/assets/76bff5f1-c821-42d7-ad36-519dce729bbd)](https://namu.wiki/w/%EB%A7%88%EC%9E%91%ED%8C%A8)


### 모든 패는 각각 4개씩 있다.

### 플레이어는 13개의 패를 받고 시작하고, 매 순서마다 패를 1개씩 받으며, 패를 받은 직후 패 1개를 골라서 버려야 한다.

### `연속된 패`는 아래를 의미한다
- 동일한 패 3개 (예: `3만`, `3만`, `3만`)
- 연속된 숫자로 패 3개(예: `1만`, `2만`, `3만`)

### 13개의 패 상태일 때, 마지막 14번째 패가 들어올 때 아래의 조건이 된다고 하면 "리치"를 선언할 수 있다.
- `3개의 연속된 패` + `3개의 연속된 패` + `3개의 연속된 패` + `3개의 연속된 패` + `2개의 같은 패`
- `1만`, `9만`, `1통`, `9통`, `1삭`, `9삭`, `동`, `남`, `서`, `북`, `백`, `발`, `중`, `아까 패들 중 아무거나 하나 더`


### 본인이 "리치" 상태일 때에 아래의 상태가 되면 승리를 선언할 수 있다.
- 본인이 받은 패가 리치를 선언할 당시 조건상태를 만족할 때 (쯔모)
- 다른 플레이어가 버린 패가 내 패였다면 리치를 선언할 당시 조건상태를 만족할 떼 (론)

### 승리 선언 예시 상태 이미지
[![image](https://github.com/user-attachments/assets/6bbc1d20-75b5-4849-aea4-d227746e3460)](https://namu.wiki/w/%EB%A6%AC%EC%B9%98%EB%A7%88%EC%9E%91#s-2.1)

### 본인이 "리치"를 선언하지 않은 상태에서는 아래의 상태가 되면 승리를 선언할 수 있다.
- 본인이 받은 패가 리치를 선언할 당시 조건상태를 만족할 때 (쯔모)
- 실제 마작에는 여러가지 규칙이 더 있지만 여기서는 설정하지 않는다.

### 패산 별 코드에 작성할 코드
- 만수패: M (예시: 1만: 1M, 6만: 6M), priority 1 ~ 9
- 통수패: P (예시: 1통: 1P, 6통: 6P), priority 10 ~ 18
- 삭수패: S (예시: 1삭: 1S, 6삭: 6S), priority 19 ~ 27
- 동패: 1Z, priority 28
- 남패: 2Z, priority 29
- 서패: 3Z, priority 30
- 북패: 4Z, priority 31
- 백패: 5Z, priority 32
- 발패: 6Z, priority 33
- 중패: 7Z, priority 34

## 프로그램 작동 방식
0. 이 프로그램은 무조건 첫번째 플레이어가 사용자이다.
1. 총 136개의 모든 패를 랜덤으로 섞어 저장해둔다. (큐/스택 사용)
2. 14개의 패는 안 쓰는 패 이므로, 없는 것으로 취급한다. (실제 게임에서는 일부 사용하기도 하지만 여기에서는 삭제한다.)
3. 플레이어 4명이 서로 1개씩을 가져간다.
4. 플레이어 4명이 서로 4개씩 패를 가져간다. 이를 3번 반복하여 1인당 총 12개 패를 각각 가져간다. 이러면 각각 총 13개의 패를 가지게 된다.
5. [출력:]() 패를 보여준다. 보여줄 때, 순서를 신경써서 보여준다. 
  - 순서: 1->9, 만수->통수->삭수->동->남->서->북->백->발->중
7. 첫번째 플레이어가 이제 1개의 패를 가져온다.
8. [출력:]() 패를 보여준다. 보여줄 때, 순서를 신경써서 보여준다.
  - 순서: 1->9, 만수->통수->삭수->동->남->서->북->백->발->중->[이번에 가져온 패]()
9. [입력:]() 첫번째 플레이어가 버릴 패를 골라서 버린다.
10. [출력:]() 이번에 버려진 패를 보여준다. 또한, 이전에 버려졌던 모든 패를 다 보여준다.
11. 두번째 ~ 네번째 사용자가 각각 첫번째 사용자가 한 것처럼 진행한다. 이때 버리는 패는, 아래의 규칙에 따른다.
  - 풍패나 삼원패 중에 연속된 패가 4개가 있다면 그 4개를 3개로 만들기 위해 해당 패를 하나 버린다. ( 백, 백, 백, 백 => 백을 1개 버린다 )
  - 풍패나 삼원패가 있는데 그 패가 2개 이상 연속되지 않는다면 (1개밖에 없다면) 그 패를 버린다.
  - 숫자패 중에 연속되지 않고 따로 떨어진 패가 있다면 그 패를 버린다.(1만, 2만, 5만, 1삭, ... => 5만을 버린다)
  - 숫자패 중에 4개만 연속된 패가 있다면 그 가장자리 두개 중 하나를 버린다 (1만, 2만, 3만, 4만 => 1만 또는 4만을 버린다)
  - 숫자패 중에 5개 이상 연속된 패가 있다면 그것들은 3개씩 나눠서 취급한다. (1만, 2만, 3만, 4만, 5만, 7만 => 1만, 2만, 3만을 하나로 취급, 4만, 5만을 하나로 취급, 따라서 7만을 버림)
  - 만일 이를 전부 확인했는데 여기까지 왔다면, "리치"를 선언할 수 없으면 아무거나 하나 버린다.
  - 리치를 걸 수 있는 상황이 되면 무조건 "리치"를 선언한다.
12. [출력:]() 만일 플레이어 중 한명 이상이 "리치"를 선언한 경우 해당 플레이어가 리치임을 사용자가 볼 수 있게 표시해준다.
13. 리치 상황에서는 위에서 "쯔모" 또는 "론"을 할 수 있는 상황이 되기 전까지는 반드시 [이번에 가져온 패]()를 버려야 한다. 다른 패는 버릴 수 없다.
14. 가장 먼저 "쯔모" 또는 "론"을 해서 승리한 플레이어를 표시한다.

## 과제?
- AI 등 다른 플레이어 2~4는 없다고 가정하고, 플레이어1 (사용자) 가 혼자서 게임을 플레이하는 게임을 만드세요. 다른 플레이어가 없으므로 승리 조건 중 "쯔모"로 승리하는것만 존재합니다.
- 전부 다 만들고 싶은 경우 만드셔도 됩니다.
- Winning.cpp 코드는 다음과 같습니다. 승리 조건은 해당 알고리즘을 복붙하여 이용하세요. 코드에 따라 알고리즘 제외한 파트에 일부 수정이 필요할 수도 있습니다. 직접 만드셔도 됩니다.
```cpp
// 승리조건 체크 CPP 파일. ChatGPT의 도움으로 완성.

#include "std.h"
// Winning 계산을 위한 알고리즘.
#include <map>
#include <algorithm>
#include <unordered_map>
#include <sstream> 
#include <string>
// Winning 계산을 위한 알고리즘 끝.

void getTileInfo(int priority, std::string& suit, int& number) {
    if (priority >= 1 && priority <= 9) {
        suit = "man"; // 만수패
        number = priority;
    }
    else if (priority >= 10 && priority <= 18) {
        suit = "pin"; // 통수패
        number = priority - 9;
    }
    else if (priority >= 19 && priority <= 27) {
        suit = "sou"; // 삭수패
        number = priority - 18;
    }
    else {
        suit = "honor"; // 자패
        number = priority; // 자패는 숫자로 구분하지 않음
    }
}

// 남은 타일로 멘츠를 만들 수 있는지 확인하는 함수
bool canFormMeldsRecursive(std::map<int, int>& counts) {
    // 모든 타일을 사용했는지 확인
    bool empty = true;
    for (const auto& pair : counts) {
        if (pair.second > 0) {
            empty = false;
            break;
        }
    }
    if (empty) {
        return true;
    }

    // 남은 타일 중 가장 작은 우선순위의 타일을 찾습니다.
    int priority = -1;
    for (const auto& pair : counts) {
        if (pair.second > 0) {
            priority = pair.first;
            break;
        }
    }
    if (priority == -1) {
        return true; // 모든 타일을 사용함
    }

    // 현재 타일로 멘츠를 시도
    bool success = false;

    int count = counts[priority];

    // 코츠를 시도
    if (count >= 3) {
        counts[priority] -= 3;
        if (canFormMeldsRecursive(counts)) {
            counts[priority] += 3; // 백트래킹
            return true;
        }
        counts[priority] += 3; // 백트래킹
    }

    // 슌츠를 시도 (자패 제외)
    std::string suit;
    int number;
    getTileInfo(priority, suit, number);

    if ((suit == "man" || suit == "pin" || suit == "sou") && number <= 7) {
        int next1 = priority + 1;
        int next2 = priority + 2;

        if (counts[next1] > 0 && counts[next2] > 0) {
            std::string suit1, suit2;
            int number1, number2;
            getTileInfo(next1, suit1, number1);
            getTileInfo(next2, suit2, number2);

            if (suit == suit1 && suit == suit2 &&
                number1 == number + 1 && number2 == number + 2) {
                counts[priority]--;
                counts[next1]--;
                counts[next2]--;
                if (canFormMeldsRecursive(counts)) {
                    counts[priority]++;
                    counts[next1]++;
                    counts[next2]++;
                    return true;
                }
                counts[priority]++;
                counts[next1]++;
                counts[next2]++;
            }
        }
    }

    // 현재 타일로 멘츠를 만들 수 없으므로 카운트를 그대로 두고 재귀 호출
    return false;
}

// 화료 패인지 확인하는 함수
bool Winning::isWinningHand(const std::vector<Tiles*>& hand) {
    if (hand.size() != 14) {
        return false;
    }

    // 타일 카운트를 만듭니다.
    std::map<int, int> tileCounts;
    for (Tiles* tile : hand) {
        int priority = tile->getPriority();
        tileCounts[priority]++;
    }

    // 가능한 모든 또이츠(짝패)를 시도합니다.
    for (auto& pair : tileCounts) {
        if (pair.second >= 2) {
            // 타일 카운트의 복사본을 만듭니다.
            std::map<int, int> counts = tileCounts;
            // 또이츠를 제거합니다.
            counts[pair.first] -= 2;

            // 나머지 타일로 멘츠를 만들 수 있는지 재귀적으로 확인합니다.
            if (canFormMeldsRecursive(counts)) {
                return true;
            }
        }
    }

    return false;
}

// 리치 선언 가능 여부를 확인하는 함수
bool Winning::canDeclareRiichi(const std::vector<Tiles*>& hand, std::vector<Tiles*>& reachhand) {
    if (hand.size() != 14) {
        return false;
    }
    reachhand.clear();
    bool canRiichi = false;

    // 각 타일을 버려봅니다.
    for (size_t i = 0; i < hand.size(); ++i) {
        // 핸드의 복사본을 만듭니다.
        std::vector<Tiles*> tempHand = hand;
        Tiles* discardedTile = tempHand[i];
        tempHand.erase(tempHand.begin() + i); // 타일을 버림

        // 가능한 모든 타일을 추가해봅니다.
        for (int j = 1; j <= 34; ++j) {
            // 새로운 타일을 추가합니다.
            Tiles* newTile = new Tiles("", "", j);
            tempHand.push_back(newTile);

            // 화료 패인지 확인합니다.
            if (isWinningHand(tempHand)) {
                canRiichi = true;
                reachhand.push_back(discardedTile);
                // 메모리 해제
                tempHand.pop_back();
                delete newTile;
                break; // 현재 버림패로 가능한 경우를 찾았으므로 다음으로
            }

            // 메모리 해제
            tempHand.pop_back();
            delete newTile;
        }
    }

    return canRiichi;
}
```
```cpp
#pragma once
class Winning
{
private:
public:
	static bool isWinningHand(const vector<Tiles*>& tiles);
	static bool canDeclareRiichi(const vector<Tiles*>& tiles, vector<Tiles*>& reachhand);
};
```

## 기타 (마작을 아는 사람들을 위해)
- "치", "퐁", "깡", "텐파이", "구종구패" 등 여러가지 기타 마작의 규칙은 (아직은) 만들지 않았습니다.
- 승리조건은 현재 리치, 멘젠쯔모, 국사무쌍 밖에 없습니다. (다만 국사무쌍은 이 코드에서는 동작을 확인해보지 못하였습니다)
- 우송대 2024년 2학기 비트단기 수업 도중에 만들어졌습니다. (학교 수업용)

![프레젠테이션1](https://github.com/user-attachments/assets/923e84f5-4f11-49e1-9bdd-753765fb1542)
