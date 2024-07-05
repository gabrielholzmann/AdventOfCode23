#include <iostream>
#include <cstring>

int getCalibrationValue(char *line) {
    char *begin = line;
    while (!isdigit(*begin)) {
        begin++;
    }

    char *end = line + strlen(line) - 1;
    while (!isdigit(*end)) {
        end--;
    }

    return (*begin - '0') * 10 + (*end - '0');
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
