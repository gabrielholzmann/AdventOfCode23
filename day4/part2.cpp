#include <iostream>
#include <cstring>
#include <unordered_map>

void calculateMatches(char *game, int gameId, std::unordered_map<int, int> &copies) {
    std::unordered_map<int, int> cardPoints;
    int totalMatches = 0;

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
            totalMatches++;
        }

        //advance by 1, so we can find the next space
        game++;

        game = strchr(game, ' ');
    }

    //if I didn't find this particular game star it with 1 copy
    if (copies.find(gameId) == copies.end())
        copies[gameId] = 1;

    for (int i = gameId + 1; i <= gameId + totalMatches; i++) {
        //if I didn't find this particular game star it with 1 copy
        if (copies.find(i) == copies.end()) {
            copies[i] = 1;
        }

        //add copies equal to the number of copies of this game
        copies[i] += copies[gameId];
    }
}


int main() {
    FILE *file = fopen("../input.txt", "r");
    if (!file) {
        std::cout << "File not found" << std::endl;
        return 1;
    }

    char card[150];
    int totalGames = 0;
    std::unordered_map<int, int> copies;

    while (fgets(card, sizeof(card), file)) {
        char *game = strchr(card, ':') + 2;

        calculateMatches(game, ++totalGames, copies);
    }

    int total = 0;
    for (int i = 1; i <= totalGames; i++)
        total += copies[i];

    std::cout << total;

    fclose(file);

    return 0;
}
