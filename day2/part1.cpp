#include <iostream>
#include <cstring>

#define MAX_RED_BALLS 12
#define MAX_GREEN_BALLS 13
#define MAX_BLUE_BALLS 14

char *getNextBall(char *game) {
    while (*game++ != '\0') {
        if (isdigit(*game)) {
            return game;
        }
    }

    return nullptr;
}

bool countBalls(char *game) {
    char color[6];
    int balls = 0;

    while (game) {
        sscanf(game, "%d %s", &balls, color);

        switch (*color) {
            case 'r':
                if (balls > MAX_RED_BALLS)
                    return false;
                break;
            case 'g':
                if (balls > MAX_GREEN_BALLS)
                    return false;
                break;
            case 'b':
                if (balls > MAX_BLUE_BALLS)
                    return false;
                break;
        }

        game = getNextBall(game);
    }

    return true;
}


int main() {
    FILE *file = fopen("../input.txt", "r");
    if (!file) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }

    char line[256];
    int possibleGames = 0;

    while (fgets(line, sizeof(line), file)) {
        int gameId = atoi(line + 5);

        char *game = strpbrk(line, ":") + 2;

        if (countBalls(game)) {
            possibleGames += gameId;
        }
    }

    std::cout << "Possible games: " << possibleGames << std::endl;

    fclose(file);

    return 0;
}
