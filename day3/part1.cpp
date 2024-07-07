#include <iostream>
#include <cstring>

bool isSymbol(char c) {
    return !isdigit(c) && c != '.' && c != '\n';
}

int checkCardinalDirections(char *map[], int numLines, int lineLength, int x, int y) {
    int total = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }

            int x1 = x + i;
            int y1 = y + j;

            if (x1 >= 0 && x1 < lineLength && y1 >= 0 && y1 < numLines) {
                if (isdigit(map[y1][x1])) {
                    while (x1 > 0 && isdigit(map[y1][x1 - 1])) {
                        x1--;
                    }
                    total +=  atoi(&map[y1][x1]);

                    //set all digits to '.' so we don't count them again
                    while (isdigit(map[y1][x1])) {
                        map[y1][x1] = '.';
                        x1++;
                    }
                }
            }
        }
    }

    return total;
}

int sumPartNumbers(char *map[], int numLines, int lineLength) {
    int total = 0;

    for (int y = 0; y < numLines; y++) {
        char *line = map[y];
        for(int x = 0; line[x] != '\0'; x++) {
            if (isSymbol(line[x])) {
                total += checkCardinalDirections(map, numLines, lineLength, x, y);
            }
        }
    }
    return total;
}

int main() {
    FILE *file = fopen("../input.txt", "r");
    if (!file) {
        std::cout << "File not found" << std::endl;
        return 1;
    }

    char *map[200];
    int numLines = 0;

    while (true) {
        map[numLines] = new char[200];

        if (fgets(map[numLines], 200, file) == nullptr) {
            break;
        }

        numLines++;
    }

    std::cout << sumPartNumbers(map, numLines, strlen(map[0]) - 1) << std::endl;

    fclose(file);

    return 0;
}
