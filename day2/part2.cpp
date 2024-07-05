#include <iostream>
#include <cstring>
#include <climits>

char *getNextBall(char *game) {
    while (*game++ != '\0') {
        if (isdigit(*game)) {
            return game;
        }
    }

    return nullptr;
}

int countBalls(char *game) {
    char color[6];
    int balls = 0;

    int minRedBalls = 0;
    int minGreenBalls = 0;
    int minBlueBalls = 0;

    while (game) {
        sscanf(game, "%d %s", &balls, color);

        switch (*color) {
            case 'r':
                if (balls > minRedBalls)
                    minRedBalls = balls;
                break;
            case 'g':
                if (balls > minGreenBalls)
                    minGreenBalls = balls;
                break;
            case 'b':
                if (balls > minBlueBalls)
                    minBlueBalls = balls;
                break;
        }

        game = getNextBall(game);
    }

    return minRedBalls * minGreenBalls * minBlueBalls;
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
        char *game = strpbrk(line, ":") + 2;

        possibleGames += countBalls(game);
    }

    std::cout << "Possible games: " << possibleGames << std::endl;

    fclose(file);

    return 0;
}
