#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

std::unordered_map<char, int> cardStrength = {
        {'2', 0},
        {'3', 1},
        {'4', 2},
        {'5', 3},
        {'6', 4},
        {'7', 5},
        {'8', 6},
        {'9', 7},
        {'T', 8},
        {'J', 9},
        {'Q', 10},
        {'K', 11},
        {'A', 12}
};

enum handStrength {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND,
};

typedef struct hand {
    char cards[6];
    int bid;
} hand;

std::vector<hand> readHands(FILE *fp) {
    char line[50];
    std::vector<hand> hands;

    while (fgets(line, 50, fp)) {
        hand h;
        sscanf(line, "%c%c%c%c%c %d\n", &h.cards[0], &h.cards[1], &h.cards[2], &h.cards[3], &h.cards[4], &h.bid);
        h.cards[5] = '\0';
        hands.push_back(h);
    }

    return hands;
}

bool breakTie(hand a, hand b) {
    for (int i = 0; i < 5; i++) {
        if (a.cards[i] != b.cards[i]) {
            return cardStrength[a.cards[i]] < cardStrength[b.cards[i]];
        }
    }
    return false;
}

handStrength checkStrength(hand h) {
    std::vector<int> cardCount(13, 0);
    for (int i = 0; i < 5; i++) {
        cardCount[cardStrength[h.cards[i]]]++;
    }

    auto appearances = [&cardCount](int n) {
        return std::count(cardCount.begin(), cardCount.end(), n);
    };

    if (appearances(5)) {
        return FIVE_OF_A_KIND;
    } else if (appearances(4)) {
        return FOUR_OF_A_KIND;
    } else if (appearances(3)) {
        return (appearances(2)) ? FULL_HOUSE : THREE_OF_A_KIND;
    } else if (appearances(2) == 2) {
        return TWO_PAIR;
    } else if (appearances(2) == 1) {
        return ONE_PAIR;
    } else {
        return HIGH_CARD;
    }

}

bool sortHands(hand a, hand b) {
   int strengthA = checkStrength(a);
   int strengthB = checkStrength(b);

   if (strengthA == strengthB) {
        return breakTie(a, b);
    } else {
        return strengthA < strengthB;
    }
}

int main() {
    FILE *file = fopen("../input.txt", "r");
    if (!file) {
        std::cerr << "Could not open file" << std::endl;
        return 1;
    }

    std::vector<hand> hands = readHands(file);

    std::sort(hands.begin(), hands.end(), sortHands);

    int totalWinnings = 0;
    for (int i = 0; i < hands.size(); i++) {
        totalWinnings += hands[i].bid * (i + 1);
    }

    std::cout << totalWinnings << std::endl;

    return 0;
}
