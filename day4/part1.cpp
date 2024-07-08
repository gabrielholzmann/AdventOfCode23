#include <iostream>
#include <cstring>
#include <unordered_map>

int calculatePoints(char *game) {
    std::unordered_map<int, int> cardPoints;
    int totalPoints = 1;

    while (*game != '|') {
        int number = atoi(game);
        cardPoints[number]++;

        //advance by 1, so we can find the next space
        game++;

        game = strchr(game, ' ') + 1;
    }

    //place game at the first space of my numbers
    game += 1;

    while (game) {
        //advance to be place at the first digit
        game++;

        int number = atoi(game);

        if (cardPoints.find(number) != cardPoints.end()) {
            totalPoints *= 2;
        }

        //advance by 1, so we can find the next space
        game++;

        game = strchr(game, ' ');
    }

    //divide by 2, because the first match doesn't count
    return totalPoints / 2;
}


int main() {
    FILE *file = fopen("../input.txt", "r");
    if (!file) {
        std::cout << "File not found" << std::endl;
        return 1;
    }

    char card[150];
    int total = 0;
    while (fgets(card, sizeof(card), file)) {
        char *game = strchr(card, ':') + 2;

        total += calculatePoints(game);
    }

    std::cout << "Total: " << total;

    fclose(file);

    return 0;
}
