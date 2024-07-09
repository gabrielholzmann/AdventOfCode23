#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

std::unordered_map<char, int> cardStrength = {
        {'J', 0},
        {'2', 1},
        {'3', 2},
        {'4', 3},
        {'5', 4},
        {'6', 5},
        {'7', 6},
        {'8', 7},
        {'9', 8},
        {'T', 9},
        {'Q', 10},
        {'K', 11},
        {'A', 12}
};

std::unordered_map<int, char> cardStrengthReverse = {
        {0, 'J'},
        {1, '2'},
        {2, '3'},
        {3, '4'},
        {4, '5'},
        {5, '6'},
        {6, '7'},
        {7, '8'},
        {8, '9'},
        {9, 'T'},
        {10, 'Q'},
        {11, 'K'},
        {12, 'A'}
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

    auto appearances = [&cardCount](int n) {
        return std::count(cardCount.begin(), cardCount.end(), n);
    };

    for (int i = 0; i < 5; i++) {
        cardCount[cardStrength[h.cards[i]]]++;
    }

    //if there's a joker
    if (cardCount[0]) {
        //set joker count to 0
        cardCount[0] = 0;
        //find most occurring card
        int maxIndex = std::max_element(cardCount.begin(), cardCount.end()) - cardCount.begin();

        //get replacement char
        char replacement = cardStrengthReverse[maxIndex];

        //replace all jokers with the most occurring card
        for (int i = 0; i < 5; i++) {
            if (h.cards[i] == 'J') {
                h.cards[i] = replacement;
                cardCount[maxIndex]++;
            }
        }
    }

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