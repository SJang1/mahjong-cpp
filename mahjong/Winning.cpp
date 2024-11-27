// 승리조건 체크 CPP 파일. ChatGPT의 도움으로 완성.

#include "std.h"


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
