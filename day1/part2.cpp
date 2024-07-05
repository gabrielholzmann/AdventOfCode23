#include <iostream>
#include <cstring>

char *strings[] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};

int getNumber(char *line) {
    if (isdigit(*line)) {
        return *line - '0';
    }

    for (int i = 0; i <= 8; ++i) {
        if (strncmp(line, strings[i], strlen(strings[i])) == 0) {
            return i + 1;
        }
    }

    return 0;
}

int getCalibrationValue(char *line) {
    char *begin = line;
    char *end = line + strlen(line) - 1;

    int firstNumber = 0;
    int lastNumber = 0;

    while (!firstNumber) {
        firstNumber = getNumber(begin++);
    }

    while (!lastNumber) {
        lastNumber = getNumber(end--);
    }

    return firstNumber * 10 + lastNumber;
}

int main() {
    FILE *file = fopen("../input.txt", "r");
    if (!file) {
        std::cout << "Error: File not found" << std::endl;
        return 1;
    }

    char line[100];
    int total = 0;

    while (fgets(line, sizeof(line), file)) {
        total += getCalibrationValue(line);
    }

    std::cout << "Total: " << total << std::endl;

    fclose(file);

    return 0;
}
