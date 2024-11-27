// �¸����� üũ CPP ����. ChatGPT�� �������� �ϼ�.

#include "std.h"


void getTileInfo(int priority, std::string& suit, int& number) {
    if (priority >= 1 && priority <= 9) {
        suit = "man"; // ������
        number = priority;
    }
    else if (priority >= 10 && priority <= 18) {
        suit = "pin"; // �����
        number = priority - 9;
    }
    else if (priority >= 19 && priority <= 27) {
        suit = "sou"; // �����
        number = priority - 18;
    }
    else {
        suit = "honor"; // ����
        number = priority; // ���д� ���ڷ� �������� ����
    }
}

// ���� Ÿ�Ϸ� ������ ���� �� �ִ��� Ȯ���ϴ� �Լ�
bool canFormMeldsRecursive(std::map<int, int>& counts) {
    // ��� Ÿ���� ����ߴ��� Ȯ��
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

    // ���� Ÿ�� �� ���� ���� �켱������ Ÿ���� ã���ϴ�.
    int priority = -1;
    for (const auto& pair : counts) {
        if (pair.second > 0) {
            priority = pair.first;
            break;
        }
    }
    if (priority == -1) {
        return true; // ��� Ÿ���� �����
    }

    // ���� Ÿ�Ϸ� ������ �õ�
    bool success = false;

    int count = counts[priority];

    // ������ �õ�
    if (count >= 3) {
        counts[priority] -= 3;
        if (canFormMeldsRecursive(counts)) {
            counts[priority] += 3; // ��Ʈ��ŷ
            return true;
        }
        counts[priority] += 3; // ��Ʈ��ŷ
    }

    // ������ �õ� (���� ����)
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

    // ���� Ÿ�Ϸ� ������ ���� �� �����Ƿ� ī��Ʈ�� �״�� �ΰ� ��� ȣ��
    return false;
}




// ȭ�� ������ Ȯ���ϴ� �Լ�
bool Winning::isWinningHand(const std::vector<Tiles*>& hand) {
    if (hand.size() != 14) {
        return false;
    }

    // Ÿ�� ī��Ʈ�� ����ϴ�.
    std::map<int, int> tileCounts;
    for (Tiles* tile : hand) {
        int priority = tile->getPriority();
        tileCounts[priority]++;
    }

    // ������ ��� ������(¦��)�� �õ��մϴ�.
    for (auto& pair : tileCounts) {
        if (pair.second >= 2) {
            // Ÿ�� ī��Ʈ�� ���纻�� ����ϴ�.
            std::map<int, int> counts = tileCounts;
            // �������� �����մϴ�.
            counts[pair.first] -= 2;

            // ������ Ÿ�Ϸ� ������ ���� �� �ִ��� ��������� Ȯ���մϴ�.
            if (canFormMeldsRecursive(counts)) {
                return true;
            }
        }
    }

    return false;
}


// ��ġ ���� ���� ���θ� Ȯ���ϴ� �Լ�
bool Winning::canDeclareRiichi(const std::vector<Tiles*>& hand, std::vector<Tiles*>& reachhand) {
    if (hand.size() != 14) {
        return false;
    }
    reachhand.clear();
    bool canRiichi = false;

    // �� Ÿ���� �������ϴ�.
    for (size_t i = 0; i < hand.size(); ++i) {
        // �ڵ��� ���纻�� ����ϴ�.
        std::vector<Tiles*> tempHand = hand;
        Tiles* discardedTile = tempHand[i];
        tempHand.erase(tempHand.begin() + i); // Ÿ���� ����

        // ������ ��� Ÿ���� �߰��غ��ϴ�.
        for (int j = 1; j <= 34; ++j) {
            // ���ο� Ÿ���� �߰��մϴ�.
            Tiles* newTile = new Tiles("", "", j);
            tempHand.push_back(newTile);

            // ȭ�� ������ Ȯ���մϴ�.
            if (isWinningHand(tempHand)) {
                canRiichi = true;
                reachhand.push_back(discardedTile);
                // �޸� ����
                tempHand.pop_back();
                delete newTile;
                break; // ���� �����з� ������ ��츦 ã�����Ƿ� ��������
            }

            // �޸� ����
            tempHand.pop_back();
            delete newTile;
        }
    }

    return canRiichi;
}
